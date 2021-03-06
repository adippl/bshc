#include "ship.h"

obj_ship*
OBJF(obj_ship,finalize)(obj_ship* this){
	this->finalize=OBJF(obj_ship,finalize);
	this->free=OBJF(obj_ship,free);
	this->clean=OBJF(obj_ship,clean);
	//this->copy=OBJF(obj_ship,copy);
	this->copyTo=NULL;
	this->objSize=sizeof(obj_ship);
	//uint16_t objName;
	
	this->shipTemplateID=0;
	this->sname=calloc(SSTRLENG,sizeof(char));
	this->sclass=calloc(SSTRLENG,sizeof(char));
	//this->hp=0;
	//this->water=0;
	//this->drag=0;
	//this->power=0;
	//this->manuver=0;
	//this->ap=0;
	//this->view=0;

	TEMPLATE3(arr,Finalize,obj_smodule)(&this->modules);
	NULL_P_CHECK(this->modules.mem);
	return(this);}

void
OBJF(obj_ship,free)(obj_ship* this){
	NULL_P_CHECK(this);
	OBJF(obj_ship,clean)(this);
	free(this);
	return;}

void
OBJF(obj_ship,clean)(obj_ship* this){
	NULL_P_CHECK(this);
	TEMPLATE3(arr,Clean,obj_smodule)(&this->modules);
	free(this->sname);
	free(this->sclass);
	return;}

obj_ship*
OBJF(obj_ship,copy)(obj_ship* this,obj_ship* dest){
	NULL_P_CHECK(this);
	NULL_P_CHECK(dest);
	STRUCTCOPPIER(dest,this,shipTemplateID);
	STRUCTCOPPIER(dest,this,factionID);
	STRUCTCOPPIER(dest,this,playerID);
	STRUCTCOPPIER(dest,this,sizex);
	STRUCTCOPPIER(dest,this,sizey);
	STRUCTCOPPIER(dest,this,centerx);
	STRUCTCOPPIER(dest,this,centery);
	STRUCTCOPPIER(dest,this,hp);
	STRUCTCOPPIER(dest,this,water);
	STRUCTCOPPIER(dest,this,drag);
	STRUCTCOPPIER(dest,this,power);
	STRUCTCOPPIER(dest,this,manuver);
	STRUCTCOPPIER(dest,this,ap);
	STRUCTCOPPIER(dest,this,view);
	strncpy(dest->sname,this->sname,SSTRLENG);
	TEMPLATE3(arr,Copyto_memcpy,obj_smodule)(&this->modules,&dest->modules);
	//TEMPLATE3(arr,Copyto,obj_smodule)(&this->modules,&dest->modules);
	
	//obj_smodule*	OBJF(obj_smodule,copyTo)(obj_smodule* this, obj_smodule* dest);
	//obj_smodule *p_tmp=NULL;
	//TEMPLATE3(arr,iterResetStart,obj_smodule)(&this->modules);
	//while((p_tmp=TEMPLATE3(arr,iterNext,obj_smodule)(&this->modules))){
	//	obj_smodule_copyTo(p_tmp,TEMPLATE3(arr,append,obj_smodule)(&dest->modules));
	//	}

	return(dest);}

void*
OBJF(obj_ship,print)(void* ap_obj){
	NULL_P_CHECK(ap_obj);
	obj_ship* this=(obj_ship*) ap_obj;
	fprintf(stderr,"\ndumping obj_ship %p\n",(void*)this);
	DUMP_STRUCT_int(this,shipTemplateID);
	DUMP_STRUCT_string(this,sname);
	DUMP_STRUCT_string(this,sclass);
	DUMP_STRUCT_int(this,factionID);
	DUMP_STRUCT_int(this,playerID);
	DUMP_STRUCT_int(this,sizex);
	DUMP_STRUCT_int(this,sizey);
	DUMP_STRUCT_int(this,centerx);
	DUMP_STRUCT_int(this,centery);
	DUMP_STRUCT_int(this,hp);
	DUMP_STRUCT_int(this,armor);
	DUMP_STRUCT_int(this,water);
	DUMP_STRUCT_int(this,drag);
	DUMP_STRUCT_int(this,manuver);
	DUMP_STRUCT_int(this,ap);
	DUMP_STRUCT_int(this,view);
	DUMP_STRUCT_int(this,visibility);
	DUMP_STRUCT_int(this,curr_hp);
	DUMP_STRUCT_int(this,curr_armor);
	DUMP_STRUCT_int(this,curr_water);
	DUMP_STRUCT_int(this,curr_drag);
	DUMP_STRUCT_int(this,curr_manuver);
	DUMP_STRUCT_int(this,curr_ap);
	DUMP_STRUCT_int(this,curr_view);
	DUMP_STRUCT_int(this,curr_visibility);
	fprintf(stderr,"modules arr at %p:\n",(void*)&this->modules);
	TEMPLATE3(arr,dump,obj_smodule)(&this->modules);
	fprintf(stderr,"\nEND of obj_ship %p\n",(void*)this);
	return(NULL);}


int
shipParse(obj_ship* this, json_stream* js){
	NULL_P_CHECK(this);
	NULL_P_CHECK(js);
	
	enum json_type type;
	const char* str=json_get_string(js,NULL);
	bool arrloop=true;
	obj_smodule* obj_smodule=NULL;
	printf("FIRST ship STRING %s\n",str);

	bool var=false;
	while(true){
		type=json_next(js);
		switch(type){
			case JSON_ERROR:
				PARSE_EMSG(js,json_typename[type]);
				fprintf(stderr,"JSON ERR %s\n",\
					json_get_error(js));
				break;
			case JSON_NULL:
			case JSON_TRUE:
			case JSON_FALSE:
			case JSON_NUMBER:
				break;
			case JSON_STRING:
				var=true;
			    break;
			case JSON_ARRAY:
			case JSON_OBJECT:
			case JSON_DONE:
				PARSE_EMSG(js,json_typename[type]);
			    break;
			case JSON_ARRAY_END:
				PARSE_EMSG(js,json_typename[type]);
				return(1);
			case JSON_OBJECT_END:
				fprintf(stderr,"SHIP END l=%ld\n",json_get_lineno(js));
				return(0);}
		if(var){
			parseVarINT(js,shipTemplateID)
			parseVarINT(js,factionID);
			parseVarINT(js,playerID);
			parseVarINT(js,sizex);
			parseVarINT(js,sizey);
			parseVarINT(js,centerx);
			parseVarINT(js,centery);
			parseVarINT(js,hp)
			parseVarINT(js,armor)
			parseVarINT(js,water)
			parseVarINT(js,drag)
			parseVarINT(js,power)
			parseVarINT(js,manuver)
			parseVarINT(js,ap)
			parseVarINT(js,visibility)
			parseVarSTR(js,sname)
			parseVarSTR(js,sclass)
			
			parseVarINT(js,curr_hp)
			parseVarINT(js,curr_armor)
			parseVarINT(js,curr_water)
			parseVarINT(js,curr_drag)
			parseVarINT(js,curr_power)
			parseVarINT(js,curr_manuver)
			parseVarINT(js,curr_ap)
			parseVarINT(js,curr_visibility)
			
			//parseARR_SKIP(js,sname)
			parseARRobj(js,modules,obj_smodule,smoduleParse,&this->modules);
			}
			//fprintf(stderr,"json %s found invalid key %s ",__func__,str);
			//type=json_next(js);
			//fprintf(stderr,"with value %s\n",str);
		}
	return(1);}




















































































//uint8_t
//rand_gen(uint8_t* spread){
//	int v=*spread+SPREAD_DEF;	//SPREAD_DEF=1 by def
//
//	int rd=0;
//	
//	rd=0;
//	rd=rand()%v;	//value
//	if(rand()%2){	// + - sigh change
//		rd=rd*(-1);
//	}
//	return(rd);
//}
//
//struct shot*
//shot_gen(uint8_t noshells,uint8_t spread){
//	
//	struct shot* shot_ptr=shot(noshells);
//	if(!shot_ptr)exit(923);
//	
//	int16_t (*shots_arr)[noshells][2]=(void*)shot_ptr->shots_ptr;	//risky FIXIT
//	
//	for(int i=0;i<noshells;i++){
//		(*shots_arr)[i][0]=rand_gen(&spread);
//		(*shots_arr)[i][1]=rand_gen(&spread);
//		fprintf(stderr,"shell nr=%d\tx=%d\ty=%d\t\n",i,(*shots_arr)[i][0],(*shots_arr)[i][1]);
//	}
//	return(shot_ptr);
//}

//void
//obj_free(void** obj_pp){	//generic destructor
//	if(!*obj_pp)exit(EXIT_FAILURE);
//	free(*obj_pp);
//	*obj_pp=NULL;
//	return;}

//constructors

//ship_r*
//ship_r_init(){
//	ship_r* ship_r_p=calloc(1,sizeof(ship_r));
//	if(!ship_r_p)exit(EXIT_FAILURE);
//	ship_r_p->dstr=obj_free;
//	
//	return(ship_r_p);}
//
//
//ship_templ*
//ship_templ_init(){
//	ship_templ* ship_templ_p=calloc(1,sizeof(ship_templ));
//	if(!ship_templ_p)exit(EXIT_FAILURE);
//	ship_templ_p->dstr=obj_free;
//	
//	return(ship_templ_p);}
//
//ship_module*
//ship_module_init(){
//	ship_module* ship_module_p=calloc(1,sizeof(ship_module));
//	if(!ship_module_p)exit(EXIT_FAILURE);
//	ship_module_p->dstr=obj_free;
//	
//	return(ship_module_p);}
//
//ship_wpn_templ*
//ship_wpn_templ_init(){
//	ship_wpn_templ* ship_wpn_templ_p=calloc(1,sizeof(ship_wpn_templ));
//	if(!ship_wpn_templ_p)exit(EXIT_FAILURE);
//	ship_wpn_templ_p->dstr=obj_free;
//	
//	return(ship_wpn_templ_p);}
//
//void
//obj_ship_abilit_free(void** obj_pp){
//	if(!*obj_pp)exit(EXIT_FAILURE);
//	ship_abilit* obj_pp_c=(ship_abilit*)*obj_pp; 
//	free(obj_pp_c->defmod_tbl_p);
//	free(obj_pp_c->actmod_tbl_p);
//	free(obj_pp_c->dmgmod_tbl_p);
//	free(obj_pp_c->dstmod_tbl_p);
//	free(*obj_pp);
//	*obj_pp=NULL;
//	return;}
//
//ship_abilit*
//ship_abilit_init(){
//	ship_abilit* ship_abilit_p=calloc(1,sizeof(ship_abilit));
//	if(!ship_abilit_p)exit(EXIT_FAILURE);
//	ship_abilit_p->dstr=obj_ship_abilit_free;
//	
//	return(ship_abilit_p);}
//
