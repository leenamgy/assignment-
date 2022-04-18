import pygame, sys, time, random
import math
from pygame.locals import *

pygame.init()
screen = pygame.display.set_mode([500,650])
menuAtivo = True

WHITE = [255, 255, 255]
BLUE = [0, 0, 255]
BLACK = [0,0,0]
GRAY = [80, 80, 255]

text = font.render("Angry GirlFriend", True, (0,0,255))
start_main_text = font_1.render("Start", True, (255,255,255))
tutorial_main_text = font_1.render("Tutorial", True, (255,255,255))


pygame.display.set_caption("Angry GirlFriend")

start_button = pygame.Rect(182,400,100,50)
quit_button = pygame.Rect(182,500,100,50)

screen.fill(WHITE)



def Ingame():
    
    character={'rect':pygame.Rect(10,200, 40,40),'color':(255,0,0),'ySpeed':0}
    
    yCoord_init=200
    
    box1_x = 500
    box1_y = 0
    box1_width = 60
    box1_height = 250

    box2_x = 500
    box2_y = box1_y + box1_height + 140
    box2_width = 60
    box2_height = 520 - box1_height

    
    box3_x = 500
    box3_y = 0
    box3_width = 60
    box3_height = 280

    box4_x = 500
    box4_y = box3_y + box3_height + 140
    box4_width = 60
    box4_height = 520 - box3_height
    
    start_time=time.time()
    
    box_1 = {'rect' : pygame.Rect(box1_x, box1_y, box1_width, box1_height),'color':(255,255,255),'xSpeed':-3,'pos':'up'}
    box_2 = {'rect' : pygame.Rect(box2_x, box2_y, box2_width, box2_height),'color':(255,255,255),'xSpeed':-3,'pos':'down'}
    box_3 = {'rect' : pygame.Rect(box3_x, box3_y, box1_width, box3_height),'color':(255,255,255),'xSpeed':-3,'pos':'up'}
    box_4 = {'rect' : pygame.Rect(box4_x, box4_y, box2_width, box4_height),'color':(255,255,255),'xSpeed':-3,'pos':'down'}
    boxes_1 = [box_1,box_2]
    boxes_2 = [box_3,box_4]

    big_boxes = [boxes_1,boxes_2]
    
    collision = True
    while collision:
    
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
       
        score = 0
        
        time.sleep(0.01)

         
        for b in boxes:

            score_text = font_2.render("Score : "+str(score), 1, (200,200,255))
            
            b['rect'].left += b['xSpeed'] 
            pygame.draw.rect(screen, b['color'], b['rect'])

            screen.blit(score_text,(155 - text.get_width() // 2, 40 - text.get_height() // 2))
            
            if b['rect'].right<0:

    
                score += 1

                print(score)
                
                b['rect'].left=500
                random_height = random.randint(0,50)
                if b['pos']=='up':
                    b['rect'].bottom -= random_height
                    
                else:
                    b['rect'].top += random_height
                    
            #CRASH

            if collision == True:
                if character['rect'].right < b['rect'].left:
                    continue
                elif character['rect'].top > b['rect'].bottom:
                    continue
                elif character['rect'].bottom < b['rect'].top:
                    continue
                #elif character['rect'].bottom >= screen.:
                 #   gameover()
                  #  collision = False
                else:
                    gameover()
                    collision = False

          
        pygame.display.update()
        
    pygame.display.flip()

def gameover():

    while True:
        
        game_over ={'rect': pygame.Rect(125,200,250,200), 'color':(255,255,0)}
        
        pygame.draw.rect(screen,(255,255,0),game_over['rect'])
        over_text = font_2.render("Game Over", True, (0,0,0))
        restart_text = font_2.render("Restart?", True, (0,0,0))

        screen.blit(over_text,(320 - text.get_width() // 2, 235 - text.get_height() // 2))
        screen.blit(restart_text,(335 - text.get_width() // 2, 275 - text.get_height() // 2))

        restart_button = {'rect' : pygame.Rect(165,330,50,40), 'color':(0,0,0)}
        pygame.draw.rect(screen,restart_button['color'],restart_button['rect'])

        over_button = {'rect' : pygame.Rect(285,330,50,40), 'color':(0,0,0)}
        pygame.draw.rect(screen,over_button['color'],over_button['rect'])
        
        for eventi in pygame.event.get():
            mouse=pygame.mouse.get_pos()
            

            if 165 <= mouse[0] <= 215 and 330 <= mouse[1] <= 370:
                if eventi.type == pygame.MOUSEBUTTONDOWN:
                    Ingame()
            elif 285 <= mouse[0] <= 335 and 330 <= mouse[1] <= 370:
                if eventi.type == pygame.MOUSEBUTTONDOWN:
                    screen.fill(WHITE)
                    return

        

        pygame.display.flip()

    return
    
    
    
running = True
while running:
    for i in pygame.event.get():
        if i.type == pygame.QUIT:
            running = False
            
            pygame.quit()
