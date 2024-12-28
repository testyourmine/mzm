from array import array
from io import BufferedReader
import shutil
import os
from PIL import Image, ImageDraw

rom: BufferedReader = open("../mzm_us_baserom.gba", "rb")

subDirs: array = []

palette: array = []

# Get the file path of the desired file name
def GetFile(filename: str):
    for root, dirs, files in os.walk(".."):
        if filename in files:
            filepath = os.path.join(root, filename)
            return filepath

# Get all file paths of the desired file extension
def GetAllFileExtensions(fileextension: str):
    for root, dirs, files in os.walk(".."):
        for file in files:
            if file.endswith(fileextension):
                file_path = os.path.join(root, file)
                subDirs.append(file_path)

# GBA format: BGR555, 5 bits for each, 1 MSB bit unused
# PNG format: RGB888, 8 bits for each, 8 MSB bit unused
def Bgr555toRgb888(rgb555: int):
    red555 = (rgb555 >> 0) & 0x1F
    green555 = (rgb555 >> 5) & 0x1F
    blue555 = (rgb555 >> 10) & 0x1F

    # Put the 5 bits into the top 8 bits, and propagate the top 3 bits down
    # Helps create a better color conversion
    red888 = (red555 << 3) | (red555 >> 2)
    green888 = (green555 << 3) | (green555 >> 2)
    blue888 = (blue555 << 3) | (blue555 >> 2)

    rgb888 = (0xFF << 24) | (red888 << 16) | (green888 << 8) | (blue888)
    return rgb888

# Convert the GBA palette to a PNG palette
def ConvertGbaPalToPngPal(pal_file: BufferedReader):
    while pal_file.peek():
        bgr555 = int.from_bytes(pal_file.read(2), "little")
        rgb888 = Bgr555toRgb888(bgr555)
        palette.append(rgb888)
        #print(hex(palette[-1]))

# Create PNG image of palette, where each row is 16 colors
def CreatePalPng_Rows():
    # Create a new image
    scale = 1
    width = 16
    height = int(len(palette) / 16)
    image = Image.new("RGB", (width * scale, height * scale))
    draw = ImageDraw.Draw(image)

    # Draw each color in the palette
    box_width = 1 * scale
    box_height = 1 * scale
    for i, color in enumerate(palette):
        #print(hex(color))
        # Get the RGB values as a tuple, since that's what it expects
        r = (color >> 16) & 0xFF
        g = (color >> 8) & 0xFF
        b = color & 0xFF
        rgb = (r, g, b)

        # Get the coordinates of square, in terms of (x0, y0) and (x1, y1)
        x0 = (i % 16) * box_width
        x1 = x0 + box_width
        y0 = int(i // 16) * box_height
        y1 = y0 + box_height

        #print(f'{x0},{y0} {x1},{y1}')
        draw.rectangle([x0, y0, x1, y1], fill=rgb)

    # Save the image
    image.save("palette.png")

# Create PNG image of palette, all in one row
def CreatePalPng():
    # Create a new image
    width = len(palette)
    height = 1
    image = Image.new("RGB", (width, height))
    draw = ImageDraw.Draw(image)

    # Draw each color in the palette
    box_width = 1
    # Draw each color in the palette
    for i, color in enumerate(palette):
        #print(hex(color))
        # Get the RGB values as a tuple, since that's what it expects
        r = (color >> 16) & 0xFF
        g = (color >> 8) & 0xFF
        b = color & 0xFF
        rgb = (r, g, b)

        x0 = i * box_width
        x1 = (i + 1) * box_width
        #print(f'{x0},{y0} {x1},{y1}')
        draw.rectangle([x0, 0, x1, height], fill=rgb)
    
    # Save the image
    image.save("palette.png")

# Example palette
pal_file_path = GetFile("AcidWorm.pal")
pal_file: BufferedReader = open(pal_file_path, "rb")

#ConvertGbaPalToPngPal(pal_file)
#CreatePalPng_Rows()

