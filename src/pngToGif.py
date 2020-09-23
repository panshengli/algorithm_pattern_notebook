# -*- coding: utf-8 -*-
import imageio
def compose_gif():
    img_paths = ["./1.PNG","./2.PNG","./3.PNG","./4.PNG","./5.PNG","./6.PNG","./7.PNG","./8.PNG","./9.PNG","./10.PNG",
                 "./11.PNG","./12.PNG","./13.PNG","./14.PNG","./15.PNG","./16.PNG","./17.PNG","./18.PNG","./19.PNG","./20.PNG","./21.PNG","./22.PNG","./23.PNG"]
    gif_images = []
    for path in img_paths:
        gif_images.append(imageio.imread(path))
    imageio.mimsave("test.gif",gif_images,fps=1)
compose_gif()