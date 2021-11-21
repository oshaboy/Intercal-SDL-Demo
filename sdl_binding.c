/*
	These Bindings are just enough to run the Demo and not much else
*/
#include <ick_ec.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <string.h>
uint16_t shared_mem[65536];
#define WINDOW_TWOSPOT_PAIR 82
#define RENDERER_TWOSPOT_PAIR 84

void * getPointer(int twospot_pair){
	uint64_t addr = ick_gettwospot(twospot_pair+1);
	addr<<=32;
	addr |= ick_gettwospot(twospot_pair);
	return (void *) addr;
}
void setPointer(int twospot_pair, void * addr){
	uint64_t addr_as_int = (uint64_t) addr;
	ick_settwospot(twospot_pair,(uint32_t)addr_as_int);
	ick_settwospot(twospot_pair+1,(uint32_t)(addr_as_int>>32));
}
ICK_EC_FUNC_START(ick_SDL_Init)
	ick_linelabel(8000);
	SDL_Init(SDL_INIT_EVERYTHING);	
ICK_EC_FUNC_END	
ICK_EC_FUNC_START(ick_SDL_CreateWindow)
	ick_linelabel(8001);
	SDL_Window * window;
	{
	char * title = (char *)(shared_mem+ick_getonespot(10)); /* very not ANSI but screw it */
	
	uint16_t width=ick_getonespot(1);
	uint16_t height=ick_getonespot(2);
	uint32_t flags=ick_gettwospot(1);
	int16_t x=ick_getonespot(3);
	int16_t y=ick_getonespot(4);
	window = SDL_CreateWindow(title, x,y,width,height,flags);
	}
	
	setPointer(WINDOW_TWOSPOT_PAIR,window);
ICK_EC_FUNC_END
ICK_EC_FUNC_START(ick_SDL_Delay)
	ick_linelabel(8002);
	SDL_Delay(ick_gettwospot(1));
ICK_EC_FUNC_END

ICK_EC_FUNC_START(ick_SDL_CreateRenderer)
	ick_linelabel(8003);
	SDL_Renderer * renderer;
	SDL_Window * window = getPointer(WINDOW_TWOSPOT_PAIR);
	int16_t index=ick_getonespot(1);
	int flags=ick_gettwospot(1);
	renderer = SDL_CreateRenderer(window,index,flags);
	setPointer(RENDERER_TWOSPOT_PAIR, renderer);
ICK_EC_FUNC_END
ICK_EC_FUNC_START(ick_SDL_SetRenderDrawColor)
	ick_linelabel(8004);
	SDL_Renderer * renderer=getPointer(RENDERER_TWOSPOT_PAIR);
	uint16_t r = ick_getonespot(1);
	uint16_t g = ick_getonespot(2);
	uint16_t b = ick_getonespot(3);
	uint16_t a = ick_getonespot(4);
	SDL_SetRenderDrawColor(renderer,r,g,b,a); 
ICK_EC_FUNC_END
ICK_EC_FUNC_START(ick_SDL_RenderClear)
	
	ick_linelabel(8005);
	SDL_Renderer * renderer=getPointer(RENDERER_TWOSPOT_PAIR);
	SDL_RenderClear(renderer);
	
	
ICK_EC_FUNC_END




ICK_EC_FUNC_START(ick_SDL_RenderPresent)
	ick_linelabel(8006);
	SDL_Renderer * renderer=getPointer(RENDERER_TWOSPOT_PAIR);
	SDL_RenderPresent(renderer);
ICK_EC_FUNC_END

ICK_EC_FUNC_START(ick_SDL_RenderDrawLine)
	ick_linelabel(8007);
	SDL_Renderer * renderer=getPointer(RENDERER_TWOSPOT_PAIR);
	int x1=ick_getonespot(1);
	int y1=ick_getonespot(2);
	int x2=ick_getonespot(3);
	int y2=ick_getonespot(4);
	SDL_RenderDrawLine(renderer,x1,y1,x2,y2);
                       
ICK_EC_FUNC_END
ICK_EC_FUNC_START(ick_SDL_PollEvent)
	ick_linelabel(8008);
	SDL_Event e;
	int status=SDL_PollEvent(&e);
	int index=ick_getonespot(1);
	memcpy(shared_mem+index, &e, sizeof(SDL_Event));
	ick_setonespot(1, status);
	
        
ICK_EC_FUNC_END
ICK_EC_FUNC_START(ick_set_mem)
	ick_linelabel(7000);
	uint16_t index=ick_getonespot(1);
	uint16_t value=ick_getonespot(2);
	shared_mem[index]=value;
ICK_EC_FUNC_END
ICK_EC_FUNC_START(ick_get_mem)
	ick_linelabel(7010);
	uint16_t index=ick_getonespot(1);
	ick_setonespot(1,shared_mem[index]);
ICK_EC_FUNC_END



