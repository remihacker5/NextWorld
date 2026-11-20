from pathlib import Path
import os
from PIL import Image

# 1. Automatically set working directory to the script's folder
script_dir = Path(__file__).resolve().parent
os.chdir(script_dir)

def generate_tif_map(image_path="your_earth_map.tif", target_height=400):
    # Open the TIFF file (it will now look directly in this folder)
    img = Image.open(image_path).convert("L")
    
    orig_width, orig_height = img.size
    aspect_ratio = orig_width / orig_height
    target_width = int(target_height * aspect_ratio * 2.0)
    
    img_resized = img.resize((target_width, target_height), Image.Resampling.NEAREST)
    
    map_lines = []
    for y in range(target_height):
        row = []
        for x in range(target_width):
            pixel_value = img_resized.getpixel((x, y))
            if pixel_value > 127:
                row.append("#")
            else:
                row.append(" ")
        map_lines.append("".join(row))
        
    output_path = "real_world_map.txt"
    with open(output_path, "w", encoding="utf-8") as f:
        f.write("\n".join(map_lines))
        
    print(f"Success! Generated {target_width}x{target_height} map and saved to '{output_path}'.")

if __name__ == "__main__":
    generate_tif_map("world.tif")