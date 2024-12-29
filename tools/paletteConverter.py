from array import array
from io import BufferedReader
import shutil
import os
from PIL import Image, ImageDraw

rom: BufferedReader = open("../mzm_us_baserom.gba", "rb")

subDirs: array = []

# Get the file path of the desired file name
def GetFile(filename: str):
    for root, dirs, files in os.walk(".."):
        if filename in files:
            filepath = os.path.join(root, filename)
            return filepath
    return ""

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
def ConvertGbaPalToPngPal(pal_file: BufferedReader, palette_array: array):
    while pal_file.peek():
        bgr555 = int.from_bytes(pal_file.read(2), "little")
        rgb888 = Bgr555toRgb888(bgr555)
        palette_array.append(rgb888)
        #print(hex(palette[-1]))

# Create PNG image of palette, where each row is 16 colors
def CreatePalPng_Rows(
    palette_array: array, # The data for the palette
    output_image: str, # The file name/directory to output the image
    palette_length: int, # The number of colors per row
):
    # Create a new image
    scale = 1
    width = palette_length
    height = int(len(palette_array) / palette_length)
    image = Image.new("RGB", (width * scale, height * scale))
    draw = ImageDraw.Draw(image)

    # Size of each pixel
    box_width = 1 * scale
    box_height = 1 * scale

    # Draw each color in the palette
    for i, color in enumerate(palette_array):
        #print(hex(color))
        # Get the RGB values as a tuple, since that's what it expects
        r = (color >> 16) & 0xFF
        g = (color >> 8) & 0xFF
        b = color & 0xFF
        rgb = (r, g, b)

        # Get the coordinates of square, in terms of (x0, y0) and (x1, y1)
        x0 = (i % palette_length) * box_width
        x1 = x0 + box_width
        y0 = (i // palette_length) * box_height
        y1 = y0 + box_height

        #print(f'{x0},{y0} {x1},{y1}')
        draw.rectangle([x0, y0, x1, y1], fill=rgb)

    # Save the image
    image.save(output_image)

# Create PNG image of palette, all in one row
def CreatePalPng(
    palette_array: array, # The data for the palette
    output_image: str, # The file name/directory to output the image
):
    # Create a new image
    scale = 1
    width = len(palette_array)
    height = 1
    image = Image.new("RGB", (width * scale, height * scale))
    draw = ImageDraw.Draw(image)

    # Size of each pixel
    box_width = 1 * scale
    box_height = 1 * scale

    # Draw each color in the palette
    for i, color in enumerate(palette_array):
        #print(hex(color))
        # Get the RGB values as a tuple, since that's what it expects
        r = (color >> 16) & 0xFF
        g = (color >> 8) & 0xFF
        b = color & 0xFF
        rgb = (r, g, b)

        # Get the coordinates of square, in terms of (x0, y0) and (x1, y1)
        x0 = i * box_width
        x1 = (i + 1) * box_width
        y0 = 0
        y1 = y0 + box_height

        #print(f'{x0},{y0} {x1},{y1}')
        draw.rectangle([x0, y0, x1, y1], fill=rgb)
    
    # Save the image
    image.save(output_image)

def PaletteConverter(
    input_palette: str, # The file name/directory of the palette to input
    png_flag: int, # 0: No PNG, 1: One row, 2: Multiple rows
    output_image: str, # The file name/directory to output the image
    colors_per_row = 16, # Number of colors per row
) -> array:
    pal_file_path = GetFile(input_palette)
    if pal_file_path == "":
        print(f'File not found: {input_palette}')
        return []
    pal_file: BufferedReader = open(pal_file_path, "rb")

    pal_array = []
    ConvertGbaPalToPngPal(pal_file, pal_array)

    if png_flag == 1:
        CreatePalPng(pal_array, output_image)
    if png_flag == 2:
        CreatePalPng_Rows(pal_array, output_image, colors_per_row)
    
    pal_file.close()
    return pal_array

'''PaletteConverter(
    input_palette="Beams.pal",
    png_flag=2,
    output_image="palette.png",
)'''
