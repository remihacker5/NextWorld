import json
import math
import urllib.parse
import urllib.request

NO_TRAIL = " "
TRAIL = "="

# Approximate bounding box around Leeds (south, west, north, east)
LEEDS_BBOX = (53.72, -1.72, 53.88, -1.38)
OVERPASS_URL = "https://overpass-api.de/api/interpreter"


import os
from pathlib import Path
import time

# 1. Automatically set working directory to the script's folder
script_dir = Path(__file__).resolve().parent
os.chdir(script_dir)

OVERPASS_URLS = [
    "https://overpass-api.de/api/interpreter",
    "https://overpass.kumi.systems/api/interpreter",
    "https://maps.mail.ru/osm/tools/overpass/api/interpreter",
]


def fetch_leeds_rail_ways(
    bbox: tuple[float, float, float, float] = LEEDS_BBOX,
    cache_file: str = "leeds_rail_cache.json",
    timeout: int = 60,
    retries_per_url: int = 2,
) -> list[list[tuple[float, float]]]:
    if os.path.exists(cache_file):
        with open(cache_file, "r", encoding="utf-8") as f:
            payload = json.load(f)
    else:
        south, west, north, east = bbox
        query = f"""
        [out:json][timeout:45];
        (
          way["railway"="rail"]["service"!~"yard|siding|spur|crossover"]({south},{west},{north},{east});
        );
        out geom;
        """
        encoded = urllib.parse.urlencode({"data": query}).encode("utf-8")
        payload = None

        for url in OVERPASS_URLS:
            for attempt in range(1, retries_per_url + 1):
                try:
                    print(f"Querying {url} (attempt {attempt}/{retries_per_url})...")
                    req = urllib.request.Request(
                        url,
                        data=encoded,
                        headers={"User-Agent": "LeedsRailAsciiMap/1.0"},
                    )
                    with urllib.request.urlopen(req, timeout=timeout) as resp:
                        payload = json.loads(resp.read().decode("utf-8"))
                    break
                except (TimeoutError, urllib.error.URLError) as exc:
                    print(f"  Failed ({exc})")
                    if attempt < retries_per_url:
                        time.sleep(2 * attempt)
            if payload is not None:
                break

        if payload is None:
            raise RuntimeError(
                "All Overpass endpoints timed out or failed. Try a smaller bbox or check your network/firewall."
            )

        with open(cache_file, "w", encoding="utf-8") as f:
            json.dump(payload, f)

    lines: list[list[tuple[float, float]]] = []
    for el in payload.get("elements", []):
        if el.get("type") == "way" and "geometry" in el:
            coords = [(pt["lat"], pt["lon"]) for pt in el["geometry"]]
            if len(coords) >= 2:
                lines.append(coords)
    return lines


def draw_line_1px(grid: list[list[str]], x0: int, y0: int, x1: int, y1: int) -> None:
    """Bresenham line rasterizer so tracks stay connected and 1 cell wide."""
    height = len(grid)
    width = len(grid[0]) if height else 0

    dx = abs(x1 - x0)
    dy = -abs(y1 - y0)
    sx = 1 if x0 < x1 else -1
    sy = 1 if y0 < y1 else -1
    err = dx + dy

    while True:
        if 0 <= x0 < width and 0 <= y0 < height:
            grid[y0][x0] = TRAIL
        if x0 == x1 and y0 == y1:
            break
        e2 = 2 * err
        if e2 >= dy:
            err += dy
            x0 += sx
        if e2 <= dx:
            err += dx
            y0 += sy


def generate_leeds_rail_map(
    filename: str = "leeds_rail.txt",
    width: int = 200,
    height: int = 200,
    bbox: tuple[float, float, float, float] = LEEDS_BBOX,
) -> None:
    ways = fetch_leeds_rail_ways(bbox)
    south, west, north, east = bbox

    mean_lat = math.radians((south + north) * 0.5)
    cos_lat = math.cos(mean_lat)

    # Adjust aspect ratio for latitude and terminal character proportions (~2:1 height:width)
    lat_span = max(1e-6, north - south)
    lon_span = max(1e-6, (east - west) * cos_lat)

    grid = [[NO_TRAIL for _ in range(width)] for _ in range(height)]

    def to_grid(lat: float, lon: float) -> tuple[int, int]:
        gx = ((lon - west) * cos_lat) / lon_span * (width - 1)
        # North is top of the map (y = 0)
        gy = (north - lat) / lat_span * (height - 1)
        return int(round(gx)), int(round(gy))

    for coords in ways:
        for i in range(len(coords) - 1):
            x0, y0 = to_grid(coords[i][0], coords[i][1])
            x1, y1 = to_grid(coords[i + 1][0], coords[i + 1][1])
            draw_line_1px(grid, x0, y0, x1, y1)

    with open(filename, "w", encoding="utf-8") as f:
        f.write("\n".join("".join(row) for row in grid) + "\n")


if __name__ == "__main__":
    generate_leeds_rail_map(filename="rail_map.txt", width=200, height=200)
    print("Generated rail_map.txt")