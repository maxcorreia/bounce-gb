#include <gb/gb.h>
#include <gb/console.h>
#include <rand.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
// Sprites
#include "ball.h"
#include "paddle1.h"
#include "paddle2.h"
#include "paddle3.h"

void main()
{
	// Initialize randomizer, print "title screen"
    printf("BOUNCE\nA Breakout clone\nBy Max Correia\n\nPress START");
    waitpad(J_START);
    // Prepares sprite positions, initialize randomizer
    printf("\n\n\n\n\n\n\n\n\n\n\n\n");
	uint16_t seed = LY_REG;
    seed |= (uint16_t)DIV_REG << 8;
    initrand(seed);
	cls();
    HIDE_SPRITES;
    // b? refers to ball position
    int bX = 78;
    int bY = 132;
    // p? refers to paddle position
    int pX = 80;
    int pY = 140;
    // bV? refers to ball velocity, determines movement
    int bVX = (rand()%3);
	int bVY = -2;
	// initialize score variable
	int score = 0;
	SPRITES_8x8;
	// ball sprite data
	set_sprite_data(0,8,ball);
	set_sprite_tile(0,0);
	set_sprite_data(1,8,paddle1);
	set_sprite_data(2,8,paddle2);
	set_sprite_data(3,8,paddle3);
	set_sprite_tile(1,1);
	set_sprite_tile(2,2);
	set_sprite_tile(3,3);
	move_sprite(1,pX-8,pY);
	move_sprite(2,pX,pY);
	move_sprite(3,pX+8,pY);
	SHOW_SPRITES;

	// Gameplay loop
    while(1) {
        // Wall/screen border collision detection
        
        
        
        bX = bX + bVX;
        bY = bY + bVY;
        move_sprite(0,bX,bY);
        move_sprite(1,pX-8,140);
	    move_sprite(2,pX,140);
	    move_sprite(3,pX+8,140);
	    
	    // Walls/bounce conditions
	    if(bY == 16){
            bVY = 2;
        }
        if(bY == 152){
            break;
        }
        if(bX == 8 || bX == 160){
            bVX = -1 * bVX;
        }
        if(bY == 132 && (bX > pX - 16) && (bX < pX + 16) && bVY == 2){
            bVX = (rand()%3);
            bVY = -2;
            score = score + 1;
            cls();
            printf("\n%d", score);
        }
        
        
	    
	    switch(joypad()){
	        case J_RIGHT:
	            if(pX == 152){
	                break;
	            }
	            pX = pX+2;
	            break;
	        case J_LEFT:
	            if(pX == 16){
	                break;
	            }
	            pX = pX-2;
	            break;
	    }
        delay(25);
    }
    cls();
    printf("\nGAME OVER");
}
