import pygame, sys, time, random
import math
from pygame.locals import *

pygame.init()
screen_height = 650
screen = pygame.display.set_mode([500,screen_height])
menuAtivo = True

WHITE = [255, 255, 255]
BLUE = [0, 0, 255]
SKY = [67,120,255]
BLACK = [0,0,0]
GRAY = [80, 80, 255]

font = pygame.font.SysFont("comicsansms", 48)
font_1 = pygame.font.SysFont("comicsansms", 24)
font_2 = pygame.font.SysFont("comicsansms",29)

text = font.render("Angry GirlFriend", True, (0,0,255))
start_main_text = font_1.render("Start", True, (255,255,255))
tutorial_main_text = font_1.render("Tutorial", True, (255,255,255))

pygame.display.set_caption("Angry GirlFriend")

start_button = pygame.Rect(182,400,100,50)
quit_button = pygame.Rect(182,500,100,50)

screen.fill(WHITE)

def Ingame():

    #BackGround

    background_image = pygame.image.load('background.jpg')

    #Bird(Charcter)
    
    character= pygame.image.load('bird.png')
    bird_x = 50
    bird_y = 300
    
    yCoord_init=200

    #OBSTACLES
    
    box1_x = 400
    box1_y = 0
    box1_width = 60
    box1_height = 230

    box2_x = 400
    box2_y = box1_y + box1_height + 155
    box2_width = 60
    box2_height = 550 - box1_height

    
    box3_x = 800
    box3_y = 0
    box3_width = 60
    box3_height = 270

    box4_x = 800
    box4_y = box3_y + box3_height + 155
    box4_width = 60
    box4_height = 550 - box3_height
    
    start_time=time.time()
    
    box_1 = {'rect' : pygame.Rect(box1_x, box1_y, box1_width, box1_height),'color':(255,255,255),'xSpeed':-2,'pos':'up'}
    box_2 = {'rect' : pygame.Rect(box2_x, box2_y, box2_width, box2_height),'color':(255,255,255),'xSpeed':-2,'pos':'down'}
    box_3 = {'rect' : pygame.Rect(box3_x, box3_y, box1_width, box3_height),'color':(255,255,255),'xSpeed':-2,'pos':'up'}
    box_4 = {'rect' : pygame.Rect(box4_x, box4_y, box2_width, box4_height),'color':(255,255,255),'xSpeed':-2,'pos':'down'}
    boxes_1 = [box_1,box_2]
    boxes_2 = [box_3,box_4]

    big_boxes = [boxes_1,boxes_2]

    score = 0
    
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
        screen.fill(SKY)
        pygame.draw.rect(screen, (255,0,0), character['rect'])
     
        #screen.blit(character_image,character['rect'].x,character['rect'].y)
        
        
        time.sleep(0.01)

        random_height = random.randint(-100,100)
         
        for boxes in big_boxes:
            
            for b in boxes:
                
                score_text = font_2.render("Score : "+str(int(score)), 1, (200,200,255))
                
                b['rect'].left += b['xSpeed'] 
                pygame.draw.rect(screen, b['color'], b['rect'])

                screen.blit(score_text,(155 - text.get_width() // 2, 40 - text.get_height() // 2))
                
                
                if b['rect'].right<0:
                    
                    score += 0.5
                    
                    b['rect'].left=800
                    
                    print(random_height)
                    if b['pos']=='up':
                        b['rect'].height += random_height
                        
                    else:
                        b['rect'].height -= random_height
                        b['rect'].top += random_height

                if collision == True:
                    if character['rect'].right < b['rect'].left:
                        continue
                    elif character['rect'].top > b['rect'].bottom:
                        continue
                    elif character['rect'].bottom < b['rect'].top:
                        continue
                    elif character['rect'].bottom == screen_height:
                        gameover()
                        collision = False
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

        yes_text = font_2.render("O", True, (WHITE))
        no_text = font_2.render("X", True, (WHITE))

        screen.blit(over_text,(320 - text.get_width() // 2, 235 - text.get_height() // 2))
        screen.blit(restart_text,(335 - text.get_width() // 2, 275 - text.get_height() // 2))

        restart_button = {'rect' : pygame.Rect(165,330,50,40), 'color':(0,0,0)}
        pygame.draw.rect(screen,restart_button['color'],restart_button['rect'])

        over_button = {'rect' : pygame.Rect(285,330,50,40), 'color':(0,0,0)}
        pygame.draw.rect(screen,over_button['color'],over_button['rect'])

        screen.blit(yes_text,(323 - text.get_width() // 2, 362 - text.get_height() // 2))
        screen.blit(no_text,(444 - text.get_width() // 2, 362 - text.get_height() // 2))
        
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
    
    
while menuAtivo:
    screen.blit(text,(240 - text.get_width() // 2, 120 - text.get_height() // 2))
    screen.blit(start_main_text,(350 - text.get_width() // 2, 440 - text.get_height() // 2))
    screen.blit(tutorial_main_text,(335 - text.get_width() // 2, 540 - text.get_height() // 2))
    for evento in pygame.event.get():
        
        mouse=pygame.mouse.get_pos()
        if  182 <= mouse[0] <= 282 and 400 <=mouse[1]<= 450:
            pygame.draw.rect(screen,(0,0,230),start_button)
            if evento.type == pygame.MOUSEBUTTONDOWN:
                print('aa')
                Ingame()
        else:
            pygame.draw.rect(screen,(0,100,180),start_button)
            
        if  182 <= mouse[0] <= 282 and 500 <=mouse[1]<= 550:
            pygame.draw.rect(screen,(230,0,0),quit_button)
            if evento.type == pygame.MOUSEBUTTONDOWN:
                print('bb')
                Tutorial()
        else:
            pygame.draw.rect(screen,(255,50,50),quit_button)
   
    pygame.display.flip()
    
running = True
while running:
    for i in pygame.event.get():
        if i.type == pygame.QUIT:
            running = False
            
            pygame.quit()
