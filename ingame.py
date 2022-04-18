import pygame, sys, time, random
import math
from pygame.locals import *

pygame.init()
screen = pygame.display.set_mode([500,600])
menuAtivo = True

WHITE = [255, 255, 255]

BLACK = [0,0,0]


text = font.render("Angry GirlFriend", True, (0,0,255))
start_main_text = font_1.render("Start", True, (255,255,255))
tutorial_main_text = font_1.render("Tutorial", True, (255,255,255))


pygame.display.set_caption("Angry GirlFriend")

start_button = pygame.Rect(182,400,100,50)
quit_button = pygame.Rect(182,500,100,50)
screen.fill(WHITE)




def Ingame():
    
    character={'rect':pygame.Rect(50,200, 40,40),'color':(255,0,0),'ySpeed':0}
    
    yCoord_init=200
    box_x = 500
    start_time=time.time()
    box_1 = {'rect' : pygame.Rect(box_x,0,60,250),'color':(255,255,255),'xSpeed':-2,'pos':'up'}
    box_2 = {'rect' : pygame.Rect(box_x,350,60,290),'color':(255,255,255),'xSpeed':-2,'pos':'down'}
    boxes = [box_1,box_2]
    while True:
    
        for event in pygame.event.get():
            if event.type == QUIT:
                pygame.quit()
                sys.exit()
            if event.type == KEYDOWN:
                
                if event.key == K_SPACE:
                        character['rect'].top+=1
                        start_time=time.time()
                        yCoord_init=character['rect'].top
                        character['ySpeed']=-450
        if character['rect'].top>600:
                start_time=time.time()
                character['rect'].top=200                   
        end_time=time.time()
        t = end_time-start_time
        character['rect'].top = ( yCoord_init + (character['ySpeed']*t) + ((1/2)*(100*9.8)*t*t) )
        screen.fill(BLUE)
        pygame.draw.rect(screen, (255,0,0), character['rect'])
        
        time.sleep(0.01)
        

        box_1['rect'].left += box_1['xSpeed'] 
        box_2['rect'].left += box_2['xSpeed']
        
        pygame.draw.rect(screen, box_1['color'], box_1['rect'])
        pygame.draw.rect(screen, box_2['color'], box_2['rect'])
        for b in boxes:
            if b['rect'].right<0:
                b['rect'].left=500
                
                if b['pos']=='up':
                    b['rect'].bottom-=100
                else:
                    b['rect'].top+=100
                

                
        pygame.display.update()
        
    pygame.display.flip()
    

running = True
while running:
    for i in pygame.event.get():
        if i.type == pygame.QUIT:
            running = False
            
            pygame.quit()
