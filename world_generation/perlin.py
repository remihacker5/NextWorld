import math
import random
import os
from pathlib import Path
# 1. Automatically set working directory to the script's folder
script_dir = Path(__file__).resolve().parent
os.chdir(script_dir)

class PerlinNoise2D:
    def __init__(self, seed: int | None = None):
        rng = random.Random(seed)
        perm = list(range(256))
        rng.shuffle(perm)
        self.perm = perm * 2

        # 8 gradient directions around the unit circle
        self.gradients = [
            (math.cos(i * math.pi / 4), math.sin(i * math.pi / 4))
            for i in range(8)
        ]

    @staticmethod
    def _fade(t: float) -> float:
        # Quintic interpolation curve: 6t^5 - 15t^4 + 10t^3
        return t * t * t * (t * (t * 6 - 15) + 10)

    @staticmethod
    def _lerp(a: float, b: float, t: float) -> float:
        return a + t * (b - a)

    def _grad(self, hash_val: int, x: float, y: float) -> float:
        gx, gy = self.gradients[hash_val % len(self.gradients)]
        return gx * x + gy * y

    def noise(self, x: float, y: float) -> float:
        """Returns 2D Perlin noise roughly in the range [-1.0, 1.0]."""
        xi = math.floor(x) & 255
        yi = math.floor(y) & 255

        xf = x - math.floor(x)
        yf = y - math.floor(y)

        u = self._fade(xf)
        v = self._fade(yf)

        aa = self.perm[self.perm[xi] + yi]
        ab = self.perm[self.perm[xi] + yi + 1]
        ba = self.perm[self.perm[xi + 1] + yi]
        bb = self.perm[self.perm[xi + 1] + yi + 1]

        x1 = self._lerp(self._grad(aa, xf, yf), self._grad(ba, xf - 1, yf), u)
        x2 = self._lerp(self._grad(ab, xf, yf - 1), self._grad(bb, xf - 1, yf - 1), u)

        return self._lerp(x1, x2, v)

    def fractal_noise(
        self,
        x: float,
        y: float,
        octaves: int = 4,
        persistence: float = 0.5,
        lacunarity: float = 2.0,
    ) -> float:
        """Combines multiple octaves of noise and normalizes to [0.0, 1.0]."""
        total = 0.0
        amplitude = 1.0
        frequency = 1.0
        max_amplitude = 0.0

        for _ in range(octaves):
            total += self.noise(x * frequency, y * frequency) * amplitude
            max_amplitude += amplitude
            amplitude *= persistence
            frequency *= lacunarity

        # Map roughly [-max_amplitude, max_amplitude] -> [0.0, 1.0]
        normalized = (total / max_amplitude) * 0.5 + 0.5
        return max(0.0, min(1.0, normalized))


def elevation_to_char(elevation: float) -> str:
    if elevation < 0.42:
        return " "   # Sea
    elif elevation < 0.48:
        return "%"   # Beaches / desert
    elif elevation < 0.61:
        return "#"   # Land
    else:
        return "@"   # Mountains


def generate_map_file(
    filename: str = "map.txt",
    width: int = 120,
    height: int = 45,
    scale: float = 18.0,
    octaves: int = 4,
    persistence: float = 0.5,
    lacunarity: float = 2.0,
    seed: int | None = 42,
) -> None:
    perlin = PerlinNoise2D(seed=seed)
    lines: list[str] = []

    for y in range(height):
        row_chars: list[str] = []
        for x in range(width):
            nx = x / scale
            ny = y / scale
            elevation = perlin.fractal_noise(
                nx,
                ny,
                octaves=octaves,
                persistence=persistence,
                lacunarity=lacunarity,
            )
            row_chars.append(elevation_to_char(elevation))
        lines.append("".join(row_chars))

    with open(filename, "w", encoding="utf-8") as f:
        f.write("\n".join(lines) + "\n")


if __name__ == "__main__":
    generate_map_file(
        filename="map.txt",
        width=200,
        height=200,
        scale=18.0,
        octaves=4,
        persistence=0.5,
        lacunarity=2.0,
        seed=42  # Set to None for a random map each run
    )
    print("Map generated and saved to map.txt")