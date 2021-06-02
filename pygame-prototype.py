import pygame
import random
import math
from opensimplex import OpenSimplex
from datetime import datetime

width, height = 600, 400

resolution = 10

screen = pygame.display.set_mode((width, height))

cols = 1 + width // resolution
rows = 1 + height // resolution
zoff = 0
seed = datetime.now().second
field = [
    [0 for row in range(rows)] for col in range(cols)
]

# transforma binario pra decimal
def get_state(a, b, c, d):
    return a * 8 + b * 4  + c * 2 + d * 1;


simplex = OpenSimplex(seed=seed)
def draw():
    global zoff, final_vertices

    for i in range(cols - 1):
        for j in range(rows - 1):
            pygame.draw.rect(screen, (255, 255, 255), (i * resolution, j * resolution, 1, 1))


    # gera terreno
    xoff = 0
    for i in range(cols):
        xoff += 0.1
        yoff = 0
        for j in range(rows):
            field[i][j] = math.ceil(simplex.noise3d(x=xoff, y=yoff, z=zoff))
            yoff += 0.1
    zoff += 0.05
    for i in range(cols - 1):
        for j in range(rows - 1):
            x = i * resolution
            y = j * resolution
            a = pygame.Vector2(x + resolution * 0.5, y)
            b = pygame.Vector2(x + resolution, y + resolution * 0.5)
            c = pygame.Vector2(x + resolution * 0.5, y + resolution)
            d = pygame.Vector2(x, y + resolution * 0.5)

            

            state = get_state(field[i][j], field[i + 1][j], field[i + 1][j + 1], field[i][j + 1])
            if state == 1:
                pygame.draw.polygon(screen, (255, 255, 255), [c, d, (x, y + resolution)])
            if state == 2:
                pygame.draw.polygon(screen, (255, 255, 255), [b, c, (x + resolution, y + resolution)])
            if state == 3:
                pygame.draw.polygon(screen, (255, 255, 255), [b, d, (x, y + resolution), (x + resolution, y + resolution)])
            if state == 4:
                pygame.draw.polygon(screen, (255, 255, 255), [a, b, (x + resolution, y)])
            if state == 5:
                pygame.draw.polygon(screen, (255, 255, 255), [a, (x + resolution, y), b, c, (x, y + resolution), d])
            if state == 6:
                pygame.draw.polygon(screen, (255, 255, 255), [a, c, (x + resolution, y + resolution), (x + resolution, y)])
            if state == 7:
                pygame.draw.polygon(screen, (255, 255, 255), [a, d, (x, y + resolution), (x + resolution, y + resolution), (x + resolution, y)])
            if state == 8:
                pygame.draw.polygon(screen, (255, 255, 255), [a, d, (x, y)])
            if state == 9:
                pygame.draw.polygon(screen, (255, 255, 255), [a, c, (x, y + resolution), (x, y)])
            if state == 10:
                pygame.draw.polygon(screen, (255, 255, 255), [(x, y), a, b, (x + resolution, y + resolution), c, d])
            if state == 11:
                pygame.draw.polygon(screen, (255, 255, 255), (a, b, (x + resolution, y + resolution), (x, y + resolution), (x , y)))
            if state == 12:
                pygame.draw.polygon(screen, (255, 255, 255), [b, d, (x, y), (x + resolution, y)])
            if state == 13:
                pygame.draw.polygon(screen, (255, 255, 255), [b, c, (x, y + resolution), (x, y), (x + resolution, y)])
            if state == 14:
                pygame.draw.polygon(screen, (255, 255, 255), [c, d, (x, y), (x + resolution, y), (x + resolution, y + resolution)])
            if state == 15:
                pygame.draw.rect(screen, (255, 255, 255), (x, y, resolution, resolution))

            
    # pygame.draw.polygon(screen, (255, 255, 255), final_vertices)
clock = pygame.time.Clock()
while True:
    clock.tick(60)
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            exit()

        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE:
                pygame.quit()
                exit()

    screen.fill((0, 0, 0))

    draw()

    pygame.display.update()
    