#include "rng.h"
#include "rng.h"
#include <stdio.h>
#include <string.h>
#include "strings.h"
#include "maintypes.h"
#include <pdcurses.h>


#define CHANCE_TO_MULTI_ON_TYPE 0.5
#define CHANCE_TO_MULTI_ON_COLOR 0.3
#define CHANCE_TO_MULTI_ON_ANY 0.1


int colorwheel[4];

void gen_type(struct card_type *t, int textnum, int id)
{

	strcpy(t->name,types_single[textnum]);
	strcpy(t->name_pl,types_pl[textnum]);
	t->id=id;
	t->enemy=t->id;
	while (t->enemy==t->id)
	t->enemy=genrand_int_n(TYPES_IN_SET);
	t->buddy=t->id;
	while ((t->buddy==t->id)||(t->buddy==t->enemy))
	t->buddy=genrand_int_n(TYPES_IN_SET); 
	t->hp_die=0.7+0.2*genrand_res53();
	t->att_die=0.6+0.2*genrand_res53();
	t->crit_die=0.2+0.2*genrand_res53();
	t->fave_ability1=genrand_int_n(N_ABILITIES)+1;
	do t->fave_ability2=genrand_int_n(N_ABILITIES)+1; 
	while ((t->fave_ability1)==(t->fave_ability2));
	return;
}

void gen_color(struct color *c)
{
	int i;
	int temparr[TYPES_IN_SET];
	
	pull_x_out_of_y(temparr,TYPES_IN_SET,TYPES_IN_SET);

	for (i=0;i<COMMON_TYPES_PER_COLOR;i++)
	c->common[i]=temparr[i];
	
	for (i=0;i<FORBIDDEN_TYPES_PER_COLOR;i++)
	c->forbidden[i]=temparr[i+COMMON_TYPES_PER_COLOR];

	for (i=0;i<TYPES_IN_SET-FORBIDDEN_TYPES_PER_COLOR-COMMON_TYPES_PER_COLOR;i++)
	c->allowed[i]=temparr[i+COMMON_TYPES_PER_COLOR+FORBIDDEN_TYPES_PER_COLOR];
	
	return;
}

void gen_abil(struct card *c, struct set *s, int n)
{
	do
	{
		if (roll_for(BASE_CHANCE_FOR_FAVORED_ABILITY))
		{
			if (roll_for(0.5))
			c->ab[n].ability_type=s->types[c->type].fave_ability1;//!
			else c->ab[n].ability_type=s->types[c->type].fave_ability2;//!
		}
		else	
		c->ab[n].ability_type=genrand_int_n(N_ABILITIES)+1;   
	}
	while (((n>0)&&(c->ab[n].ability_type==c->ab[0].ability_type))||((n>1)&&(c->ab[n].ability_type==c->ab[1].ability_type)));

	if (ability_effects[c->ab[n].ability_type]!=SPECIAL)
	{
		if (roll_for(0.3))
		{
			c->ab[n].target_by=LOCAL;//!!
		}
		else
		if (roll_for(0.55))
		{	 	  
			c->ab[n].target_by=CARDTYPE;
			
			if (ability_effects[c->ab[n].ability_type]==BENEFIT)
			{
				if (roll_for(0.7))
				{
					if (roll_for(0.5))
					c->ab[n].target_detail=c->type;
					else c->ab[n].target_detail=s->types[c->type].buddy;
				}
				else c->ab[n].target_detail=genrand_int_n(TYPES_IN_SET);
			}
			if (ability_effects[c->ab[n].ability_type]==HARM)
			{
				if (roll_for(0.5))
				c->ab[n].target_detail=s->types[c->type].enemy;
				else c->ab[n].target_detail=genrand_int_n(TYPES_IN_SET);
			}
			if ((ability_multihit[c->ab[n].ability_type])&&(roll_for(CHANCE_TO_MULTI_ON_TYPE)))
			c->ab[n].multihit=1;
			else c->ab[n].multihit=0;
		}
		else 
		if (roll_for(0.66))
		{
			c->ab[n].target_by=COLOR;
			/*****************************************/		
			if (ability_effects[c->ab[n].ability_type]==BENEFIT)
			{
				if (roll_for(0.5))		  
				c->ab[n].target_detail=c->color;					  
				else c->ab[n].target_detail=genrand_int_n(4);
			}
			if (ability_effects[c->ab[n].ability_type]==HARM)
			{
				if (roll_for(0.5))
				c->ab[n].target_detail=s->setcolors[c->color].hated_color;
				else c->ab[n].target_detail=genrand_int_n(4);
			}
			if ((ability_multihit[c->ab[n].ability_type])&&(roll_for(CHANCE_TO_MULTI_ON_COLOR)))
			c->ab[n].multihit=1;
			else c->ab[n].multihit=0;
			/****************************/		 
		}
		else 
		{
			c->ab[n].target_by=ANY;
			if ((ability_multihit[c->ab[n].ability_type])&&(roll_for(CHANCE_TO_MULTI_ON_ANY)))
			 c->ab[n].multihit=1;
			else c->ab[n].multihit=0;		
			
		}
		
	}

	return;
}

void gen_card(struct card *c,int color,struct set * s)
{
	
	c->color=color;	
	strcpy(c->name,firstnames[genrand_int_n(N_FNAMES)]);
	strcat(c->name," ");strcat(c->name,lastnames[genrand_int_n(N_LNAMES)]);
	if (roll_for(BASE_CHANCE_FOR_COMMON_TYPE))
	c->type=(s->setcolors[color]).common[genrand_int_n(COMMON_TYPES_PER_COLOR)];
	else
	/*What am I doing...*/
	c->type=s->setcolors[color].allowed[genrand_int_n(TYPES_IN_SET-COMMON_TYPES_PER_COLOR-FORBIDDEN_TYPES_PER_COLOR)];
	if (roll_for(CHANCE_FOR_DUAL_TYPE))
	{
		c->dual = 1;
		do
		{
			if (roll_for(BASE_CHANCE_FOR_COMMON_TYPE))
			c->type2=s->setcolors[color].common[genrand_int_n(COMMON_TYPES_PER_COLOR)];
			else
			
			c->type2=s->setcolors[color].allowed[genrand_int_n(TYPES_IN_SET-COMMON_TYPES_PER_COLOR-FORBIDDEN_TYPES_PER_COLOR)];
		} while (c->type2==c->type);
	}
	else c->dual=0;
	c->att=1+genrand_int_n(3); while (roll_for(s->types[c->type].att_die)) (c->att)++;
	c->hp=2+genrand_int_n(9);; while (roll_for(s->types[c->type].hp_die)) (c->hp)+=3;
	c->crit=1+genrand_int_n(3);; while (roll_for(s->types[c->type].crit_die)) (c->hp)+=1;
	c->n_abil=0;
	
	if (roll_for(CHANCE_FOR_FIRST_ABILITY))
	{
		(c->n_abil)++;
		gen_abil(c,s,0);
		if (roll_for(CHANCE_FOR_SECOND_ABILITY))
		{
			(c->n_abil)++;
			gen_abil(c,s,1);
			if (roll_for(CHANCE_FOR_THIRD_ABILITY))
			{
				(c->n_abil)++;
				gen_abil(c,s,2);
			}
		}
	}
	
	return;
}

void gen_game()
{
	pull_x_out_of_y(colorwheel,4,4);
}

void gen_set(struct set *s, unsigned long seed)
{
	int i,j;

	/*Picking what types there will be*/
	init_genrand(seed);
	s->seed=seed;
	gen_game();
	pull_x_out_of_y(s->type_ids,TYPES_IN_SET,N_TYPES);
	for (i=0;i<TYPES_IN_SET;i++)
	{
		gen_type(&(s->types[i]),s->type_ids[i],i);
	}

	/*Picking which types are associated with which color*/
	for (i=0;i<4;i++)	
	{
		gen_color(&(s->setcolors[i]));

	}
	
	for (i=0;i<3;i++)	
	s->setcolors[colorwheel[i]].hated_color=colorwheel[i+1];
	s->setcolors[colorwheel[3]].hated_color=colorwheel[0];
	/*Ugly as heck*/

	/*Actually generating cards*/
	for (i=0;i<4;i++)
	for (j=0;j<CARDS_PER_COLOR;j++)
	gen_card(&(s->cardlist[i*CARDS_PER_COLOR+j]),i,s);
	return;
}






void print_spoiler(struct set * s)
{
 FILE * f;
 char filename[40];
 char bignum[15];
 int i,j;
 
 strcpy(filename,"s");
 sprintf(bignum,"%d",s->seed);  
 strcat(filename,bignum); 
 strcat(filename,".txt");
 printw("Generating %s\n",filename);
 getch();
 f=fopen(filename,"w");
 fprintf(f,"Set %d\n",s->seed);
 fprintf(f,"CARD TYPES\n");
for (i=0;i<10;i++)
	{
		fprintf(f,"%s hate %s and love %s\n",s->types[i].name_pl,s->types[s->types[i].enemy].name_pl,s->types[s->types[i].buddy].name_pl);
		fprintf(f,"They use %s and %s.\n\n",abilities[s->types[i].fave_ability1],abilities[s->types[i].fave_ability2]);
	}
	fprintf(f,"\nCOLORS\n\n");
	for (i=0;i<4;i++) 
	{
		fprintf(f,"%s:\n",colors[i]);
		fprintf(f,"Common types:\n");
		for (j=0;j<COMMON_TYPES_PER_COLOR;j++)
		fprintf(f," %s\n",s->types[s->setcolors[i].common[j]].name);
		fprintf(f,"Forbidden types:\n");
		for (j=0;j<FORBIDDEN_TYPES_PER_COLOR;j++)
		fprintf(f," %s\n",s->types[s->setcolors[i].forbidden[j]].name);
		fprintf(f,"Hated color: %s\n\n",colors[s->setcolors[i].hated_color]);

	}
	fprintf(f,"CARDS:\n");
	for (i=0;i<CARDS_IN_SET;i++)
	{
		fprintf(f,"%d: %s \n%s %s",i+1,s->cardlist[i].name,colors[s->cardlist[i].color],s->types[s->cardlist[i].type].name);
		if (s->cardlist[i].dual) fprintf(f,"/%s ",s->types[s->cardlist[i].type2].name); else fprintf(f," ");
		fprintf(f,"ATT:%d, CRIT:%d, HP:%d\n",s->cardlist[i].att,s->cardlist[i].crit,s->cardlist[i].hp);
		if (s->cardlist[i].n_abil==0) fprintf(f,"No abilities"); else
		for (j=0;j<s->cardlist[i].n_abil;j++)
		{
			fprintf(f,"%s ",abilities[s->cardlist[i].ab[j].ability_type]);
			if (ability_effects[s->cardlist[i].ab[j].ability_type]!=SPECIAL)
			{
				if (s->cardlist[i].ab[j].target_by==LOCAL)
				{
					if (ability_effects[s->cardlist[i].ab[j].ability_type]==HARM)
					fprintf(f,"opposing card. ");
					else fprintf(f,"self. ");
				}
				else 
				{
					if (s->cardlist[i].ab[j].multihit==1)
					fprintf(f,"all of ");
					else fprintf(f,"one of ");
					
				 	if (ability_effects[s->cardlist[i].ab[j].ability_type]==HARM)
					fprintf(f,"enemy ");
					else fprintf(f,"ally ");
					
					switch(s->cardlist[i].ab[j].target_by)
					{
					 case CARDTYPE:
					 //fprintf(f,"t %d ",s->cardlist[i].ab[j].target_detail);
					  fprintf(f,"%s ",s->types[s->cardlist[i].ab[j].target_detail].name_pl);
					 break;
					 case COLOR:
					 fprintf(f,"%s ",colors[s->cardlist[i].ab[j].target_detail]);
					 //fprintf(f,"c %d ",s->cardlist[i].ab[j].target_detail);
					 break;
					 case ANY:
					  fprintf(f,"cards ");
					 break;
					 default:
					  fprintf(f,"?!%d?!",s->cardlist[i].ab[j].target_by);
					 break;
					}
				}
			}
		 fprintf(f,"\n");
		}
		fprintf(f,"\n\n");
	}
 fclose(f);
 printw("Done.\n");
 getch();
 erase();
 return;
}



