from array import array
from io import BufferedReader
import shutil
import os
import paletteConverter as pal
from PIL import Image, ImageDraw

rom: BufferedReader = open("../mzm_us_baserom.gba", "rb")

subDirs: array = []

sprite: array = []

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

# Convert the GBA GFX file to a PNG format
def ConvertGbaGfxToPng(spr_file: BufferedReader):
    while spr_file.peek():
        byte = int.from_bytes(spr_file.read(1), "little")

        # 4 BPP, so each 4 bits indexes into the palette
        high_nybble = (byte >> 4) & 0xF
        low_nybble = (byte >> 0) & 0xF
        
        # Get the color index for the high and low 4 bits (nybble)
        high_indexed_color = pal.palette[16 * 2 + high_nybble]
        low_indexed_color = pal.palette[16 * 2 + low_nybble]

        sprite.append(low_indexed_color)
        sprite.append(high_indexed_color)

# Create PNG image of sprite
def CreateSprPng_Rows():
    # Create a new image
    # Each sprite is 8x8, laid out horizontally
    width = 8 * 8 * 2
    height = 8 * 4
    image = Image.new("RGB", (width, height))
    draw = ImageDraw.Draw(image)

    # Draw each color in the palette
    box_width = 1
    box_height = 1
    offset_x = 0
    offset_y = 0
    for i, color in enumerate(sprite):
        #print(hex(color))
        # Get the RGB values as a tuple, since that's what it expects
        r = (color >> 16) & 0xFF
        g = (color >> 8) & 0xFF
        b = color & 0xFF
        rgb = (r, g, b)

        # After each 8x8 sprite, lay the next sprite horizontal to it
        if i > 0 and i % (8*8) == 0:
            offset_x += 8
        
        # After 16 sprites, go back to next row
        if i > 0 and i % (64 * 16) == 0:
            offset_x = 0
            offset_y += 8

        # Get the coordinates of square, in terms of (x0, y0) and (x1, y1)
        x0 = (i % 8) * box_width + offset_x
        x1 = x0 + box_width
        y0 = (int(i // 8) * box_height) % 8 + offset_y
        y1 = y0 + box_height

        #print(f'{x0},{y0} {x1},{y1}')
        draw.rectangle([x0, y0, x1, y1], fill=rgb)

    # Save the image
    image.save("sprite.png")

# Example sprite
pal.ConvertGbaPalToPngPal(pal.pal_file)

sprite_file_path = GetFile("IceBeamTop.gfx")
sprite_file: BufferedReader = open(sprite_file_path, "rb")
ConvertGbaGfxToPng(sprite_file)
sprite_file.close()

sprite_file_path = GetFile("IceBeamBottom.gfx")
sprite_file: BufferedReader = open(sprite_file_path, "rb")
ConvertGbaGfxToPng(sprite_file)
sprite_file.close()

sprite_file_path = GetFile("IceBeamChargedTop.gfx")
sprite_file: BufferedReader = open(sprite_file_path, "rb")
ConvertGbaGfxToPng(sprite_file)
sprite_file.close()

sprite_file_path = GetFile("IceBeamChargedBottom.gfx")
sprite_file: BufferedReader = open(sprite_file_path, "rb")
ConvertGbaGfxToPng(sprite_file)
sprite_file.close()

CreateSprPng_Rows()
