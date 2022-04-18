from pygame.locals import *

import pygame
import sys

GRAVITY = 1.2

class Player:
    def __init__(self, x, y):
        self.rect = pygame.Rect(x, y, 25, 25)
        self.yvel = 0

    def tick(self):
        self.yvel += GRAVITY

        self.rect.y += int(self.yvel)

        if self.rect.y >= 475:
            self.rect.y = 475
            self.yvel = 0

    def set(self, y):
        if y:
            self.yvel = y

class Block:
    def __init__(self, x, y, w, h):
        self.rect = pygame.Rect(x, y, w, h)

class Game:
    def __init__(self):
        pygame.init()
        self.screen = pygame.display.set_mode((500, 500))
        self.player = Player(0, 0)
        self.block = Block(200, 400, 200, 50)

    def main(self):
        right = left = False
        while True:
            self.screen.fill((230, 230, 230))
            pygame.draw.rect(self.screen, (40, 0, 255), self.block.rect)

            pygame.display.flip()
            for event in pygame.event.get():
                if event.type == QUIT:
                    pygame.quit()
                    sys.exit(0)
                elif event.type == KEYDOWN:
                    if event.key == K_SPACE:
                        self.player.set(-20)
                    elif event.key == K_RIGHT:
                        right = True
                    elif event.key == K_LEFT:
                        left = True
                elif event.type == KEYUP:
                    if event.key == K_RIGHT:
                        right = False
                    elif event.key == K_LEFT:
                        left = False

            if right:
                self.player.rect.x += 5
                while self.player.rect.colliderect(self.block.rect):
                    self.player.rect.x -= 1
            if left:
                self.player.rect.x -= 5
                while self.player.rect.colliderect(self.block.rect):
                    self.player.rect.x += 1
            self.player.tick()
            if self.player.yvel > 0:
                while self.player.rect.colliderect(self.block.rect):
                    self.player.rect.y -= 1
                    self.player.yvel = 0
            elif self.player.yvel < 0:
                while self.player.rect.colliderect(self.block.rect):
                    self.player.rect.y += 1
                    self.player.yvel = 0

game = Game()
game.main()
