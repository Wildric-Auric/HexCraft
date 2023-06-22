from PIL import Image

def add_images(img1, img2, output_path):
    # Open the images
    image1 = Image.open(img1)
    image2 = Image.open(img2)

    # Ensure both images have the same size
    if image1.size != image2.size:
        raise ValueError("Images must have the same size")

    # Create a new image with the same size
    result_image = Image.new("RGB", image1.size)

    # Get pixel data from both images
    pixels1 = image1.load()
    pixels2 = image2.load()

    # Perform pixel-wise addition
    for i in range(result_image.size[0]):
        for j in range(result_image.size[1]):
            # Get pixel colors
            color1 = pixels1[i, j]
            color2 = pixels2[i, j]

            # Calculate the sum of each color channel
            red = color1[0] + color2[0]
            green = color1[1] + color2[1]
            blue = color1[2] + color2[2]

            # Ensure the resulting color values are within the valid range (0-255)
            red = min(255, red)
            green = min(255, green)
            blue = min(255, blue)

            # Set the resulting color in the new image
            result_image.putpixel((i, j), (red, green, blue))

    # Save the resulting image
    result_image.save(output_path)
    print("Image saved to", output_path)

# Example usage
img1_path = "NoiseFreq1.png"
img2_path = "NoiseFreq2.png"
output_path = "result.png"

add_images(img1_path, img2_path, output_path)