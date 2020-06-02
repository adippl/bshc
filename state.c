#include "state.h"


//obj_resources* 
//resources_init(){
//	return(calloc(1,sizeof(obj_resources)));}

obj_resources*
resourcesFinalize(obj_resources* this){
	this->finalize=resourcesFinalize;
	this->free=resourcesFree;
	this->clean=resourcesClean;
	//this->copy=resourcesCopy;
	//CAT(obj,T)* (*copyDeep)(CAT(obj,T)* p_struct);
	this->copyDeep=NULL;
	this->objSize=sizeof(obj_resources);
	//uint16_t objName;
	
	this->vers=1;
	
	TEMPLATE3(arr,Finalize,obj_ship)(&this->shipTeplates);
	return(this);}

void
resourcesFree(obj_resources* this){
	NULL_P_CHECK(this);
	TEMPLATE3(arr,Clean,obj_ship)(&this->shipTeplates);
	free(this);
	return;}


void
resourcesClean(obj_resources* this){
	NULL_P_CHECK(this);
	TEMPLATE3(arr,Clean,obj_ship)(&this->shipTeplates);
	return;}

obj_resources*
resourcesCopy(obj_resources* this){
	NULL_P_CHECK(this);
	obj_resources* ptr=calloc(1,sizeof(obj_resources));
	NULL_P_CHECK(ptr);
	TEMPLATE3(arr,Finalize,obj_ship)(&ptr->shipTeplates);
	TEMPLATE3(arr,Copyto,obj_ship)(&this->shipTeplates,&ptr->shipTeplates);
	return(ptr);}


int
resourcesParse(obj_resources* this, json_stream* js){
	NULL_P_CHECK(this);
	NULL_P_CHECK(js);
	
	enum json_type type;
	const char* str=json_get_string(js,NULL);
	obj_ship* ship=NULL;
	bool value,arrloop=true,var=false;
	//double number;
	//bool loop=true;
	type=json_next(js);
	if(type!=JSON_OBJECT)return(2);
	while(true){
		value=false;
		type=json_next(js);
		switch(type){
			case(JSON_OBJECT_END):
			case(JSON_ERROR):
			case(JSON_NULL):
			case(JSON_DONE):
			case(JSON_ARRAY):
				//skipToArrEnd(js);
				//break;
			case(JSON_OBJECT):
				PARSE_EMSG(js,json_typename[type]);
				return(2);
			case(JSON_STRING):
				value=true;
				break;
				//skipToArrEnd(js);
				break;
			default:
				fprintf(stderr,"parsErr %s wrong node type %s\n" \
					,__func__,json_typename[type]);
				break;}
	if(value){
		parseVarINT(js,vers);
		
		if(strcmp("shipTemplates",str)==0){
			if(json_next(js)!=JSON_ARRAY)continue;
			while(arrloop){
				var=false;
				switch(type){	
					case JSON_NULL:
					case JSON_TRUE:
					case JSON_FALSE:
					case JSON_NUMBER:
					case JSON_STRING:
					case JSON_ARRAY:
						PARSE_EMSG(js,json_typename[type]);
					    break;
					case JSON_OBJECT:
						var=true;
						break;
					case JSON_OBJECT_END:
					case JSON_ERROR:
					case JSON_DONE:
						PARSE_EMSG(js,json_typename[type]);
					    break;
					case JSON_ARRAY_END:
						//json_next(js);
						arrloop=false;
						break;}
				if(var){
					printf("\t JSON passed to  %s\n",json_typename[type]);
					ship=TEMPLATE3(arr,append,obj_ship)(&this->shipTeplates);
					if(!ship)return(2);
					shipParse(ship,js);
					printf("\t JSON after ship  %s\n",json_typename[type]);
					if(json_peek(js)==JSON_OBJECT)continue;
					}
				type=json_next(js);}}}}}

	
int
resources_Dump(obj_resources* this){
	NULL_P_CHECK(this);
	fprintf(stderr,"\n\ndumping obj_resources at %p :\n",(void*)this);
	fprintf(stderr,"vers: %d\n",this->vers);
	fprintf(stderr,"shipTeplates arr at %p:\n",(void*)&this->shipTeplates);
	TEMPLATE3(arr,dump,obj_ship)(&this->shipTeplates);
	fprintf(stderr,"\nEND of obj_resources at %p :\n",(void*)this);
	return(0);}
