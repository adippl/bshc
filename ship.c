#include "ship.h"

obj_ship*
shipFinalize(obj_ship* this){
	this->finalize=shipFinalize;
	this->free=shipFree;
	this->copy=shipCopy;
	this->copyDeep=NULL;
	this->objSize=sizeof(obj_ship);
	//uint16_t objName;
	
	this->shipTemplateID=0;
	this->name=calloc(SSTRLENG,sizeof(char));
	this->hp=0;
	this->water=0;
	this->drag=0;
	this->power=0;
	this->manuver=0;
	this->ap=0;
	this->view=0;

	TEMPLATE3(arr,Finalize,obj_smodule)(&this->modules);
	//NULL_P_CHECK(this->modules.p_array);
	return(this);}

void
shipFree(obj_ship* this){
	NULL_P_CHECK(this);
	TEMPLATE3(arr,Clean,obj_smodule)(&this->modules);
	free(this->name);
	free(this);
	return;}

void
shipClean(obj_ship* this){
	NULL_P_CHECK(this);
	TEMPLATE3(arr,Clean,obj_smodule)(&this->modules);
	free(this->name);
	return;}

obj_ship*
shipCopy(obj_ship* this){
	NULL_P_CHECK(this);
	obj_ship* ptr=calloc(1,sizeof(obj_ship));
	this->finalize(ptr);
	STRUCTCOPPIER(ptr,this,shipTemplateID);
	STRUCTCOPPIER(ptr,this,hp);
	STRUCTCOPPIER(ptr,this,water);
	STRUCTCOPPIER(ptr,this,drag);
	STRUCTCOPPIER(ptr,this,power);
	STRUCTCOPPIER(ptr,this,manuver);
	STRUCTCOPPIER(ptr,this,ap);
	STRUCTCOPPIER(ptr,this,view);
	strncpy(ptr->name,this->name,SSTRLENG);
	TEMPLATE3(arr,Copyto,obj_smodule)(&this->modules,&ptr->modules);
	return(ptr);}
//obj_ship* (*copyDeep)(obj_ship* p_struct);



/*
int
shipParse(obj_ship* this, json_stream* js){
	NULL_P_CHECK(this);
	NULL_P_CHECK(js);
	
	enum json_type type;
	const char* str=NULL;
	type=json_next(js);
	if(type!=JSON_OBJECT)return(2);
	while(true){
		type=json_next(js);
		switch(type){
			case(JSON_OBJECT_END):
				return(0);
			case(JSON_ERROR):
			case(JSON_DONE):
			case(JSON_OBJECT):
				return(3);
			case(JSON_STRING):
				str=json_get_string(js,NULL);
				break;
			//case(JSON_NUMBER):
			//	number=json_get_number(js);
			//	break;
			case(JSON_ARRAY):
				skipToArrEnd(js);
				break;
			default:
				fprintf(stderr,"parsErr %s wrong node type %s\n",\
					__func__,json_typename[type]);
				break;}
	
	//if(strcmp("name",str)==0){
	//	if(json_next(js)==JSON_STRING){
	//		this->name=(int)json_get_string(js,NULL);}
	//	else{
	//		PARSE_EMSG(js,"value is not a string\n");}}
	parseVarINT(js,shipTemplateID);
	parseVarINT(js,hp);
	parseVarINT(js,drag);
	parseVarINT(js,power);
	parseVarINT(js,manuver);
	parseVarINT(js,ap);
	parseVarINT(js,view);
	parseVarINT(js,visibility);
	parseVarSTR(js,name);
	}
	return(0);}
*/

int
shipParse(obj_ship* this, json_stream* js){
	NULL_P_CHECK(this);
	NULL_P_CHECK(js);
	
	enum json_type type=json_peek(js);
	const char* str=json_get_string(js,NULL);
printf("SHIPPARSE FIRST OBJECT PASSED %s\n",json_typename[type]);
	/*if(type!=JSON_OBJECT)return(2); entering function moves json stream 
										one place ahead. no idea why */

	bool var=false;
	while(true){
		switch(type){
			case JSON_NULL:
			case JSON_TRUE:
			case JSON_FALSE:
			case JSON_NUMBER:
				printf("\t yARRLOOP BB %s\n",json_typename[type]);
			    break;
			case JSON_STRING:
				var=true;
			    break;
			case JSON_ARRAY:
			case JSON_OBJECT:
			case JSON_ERROR:
			case JSON_DONE:
				PARSE_EMSG(js,"unexpected JSON ERROR");
			    break;
			case JSON_ARRAY_END:
				PARSE_EMSG(js,"unexprcted array end");
				return(1);
			case JSON_OBJECT_END:
				return(0);}
		if(var){
			parseVarINT(js,shipTemplateID)
			parseVarINT(js,hp)
			parseVarINT(js,water)
			parseVarINT(js,drag)
			parseVarINT(js,power)
			parseVarINT(js,manuver)
			parseVarINT(js,ap)
			parseVarINT(js,visibility)
			parseVarSTR(js,name)
			}

		type=json_next(js);
		}
		
	
	return(1);}

void* TEMPLATE(obj_ship,dump)(void* ap_obj){
	NULL_P_CHECK(ap_obj);
	obj_ship* this=(obj_ship*) ap_obj;
	fprintf(stderr,"\ndumping obj_ship %p\n",(void*)this);
	DUMP_STRUCT_int(this,shipTemplateID);
	DUMP_STRUCT_string(this,name);
	DUMP_STRUCT_int(this,hp);
	DUMP_STRUCT_int(this,water);
	DUMP_STRUCT_int(this,drag);
	DUMP_STRUCT_int(this,manuver);
	DUMP_STRUCT_int(this,ap);
	DUMP_STRUCT_int(this,view);
	DUMP_STRUCT_int(this,visibility);
	fprintf(stderr,"\nend of obj_ship %p\n",(void*)this);
	return(NULL);}



























































































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
