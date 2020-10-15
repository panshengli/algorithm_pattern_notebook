# -*- coding: utf-8 -*-
import imageio
def compose_gif():
    img_paths = ["./1.jpg","./2.jpg","./3.jpg","./4.jpg","./5.jpg"]
    gif_images = []
    for path in img_paths:
        gif_images.append(imageio.imread(path))
    imageio.mimsave("test.gif",gif_images,fps=0.5)
compose_gif()
