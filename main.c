
#include "conf.h"
#include "state.h"
#include "term.h"




int 
main(int argc, char **argv){
//	setlocale(LC_ALL, "C.UTF-8");
	setlocale(LC_ALL, "en_US.utf8");
	
//	resizexy(80,24);
	int32_t c=0;

	struct chfb* p=fb_draw_map(fb_init());
	
	clear();
	do{
	//clear();
	gotoxy(0,0);
	fb_screen_draw(p);
	gotoxy(1,SIZE_Y*2+1+1);
	c=getchar();
	}while(c!='q');
	fb_free(&p);


	struct state* s=state_init(2);
	fprintf(stderr,"\n!init=%p!\n",(void*)s);
	state_free(&s);
	fprintf(stderr,"\n!free=%p!\n",(void*)s);
	
	//void* ptr=(void*)fld_init(2);
	//fprintf(stderr,"init=%p\n",ptr);
	//fld_free(&ptr);
	//fprintf(stderr,"free=%p\n",(void*)s);

	//fprintf(stdout,"\n");
	//for(int i=0;i<11;i++){
	//	fprintf(stdout,"%lc\n",FRAMECHARS[i]);
	//}
	//fprintf(stdout,"\nfield test\n");
	//
	printf("\nlel\n");
	c=getchar();
	printf("%d",c);
	prtnch('a',2,31,1);
	prtnch('a',1,31);
	prtnch(0x2693,2,34,1);

	struct state* st_p=state_init(2);
	//	(*st_p->pln+0)->shtbl_size+0
	ship_place(st_p,(*st_p->ply_ptr+0)->shtbl_ptr+0,0,0,0);
	char test=ship_placecheck(st_p,(*st_p->ply_ptr+0)->shtbl_ptr+0,0,0,0);
	printf("test=%d",test);
	
} 	
