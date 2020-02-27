#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct trans_s {
	
	int stateO;
	char w;
	char m;
	char primo;
	struct trans_s *next;
} trans_t;

typedef struct acc_s {
	
	int s;
	struct acc_s * next2;
	
} acc_t;

typedef struct statePosCurr_s {
	
	char* stringa2;
	int stateC;
	int indice;
	int lungh;
	struct statePosCurr_s * next;
	struct statePosCurr_s * prev;
	
}statePosCurr_t;

trans_t* instesta(trans_t*, char,char, int);
trans_t* inscoda(trans_t*, char,char, int);
acc_t* instestaAcc(acc_t*, int);
statePosCurr_t* inscodaSPC(statePosCurr_t*, char*, int, int,int);
statePosCurr_t* insMezzoSPC(statePosCurr_t*, char*, int, int,int);
statePosCurr_t* eliminaElSpc(statePosCurr_t*, char*);

int main(int argc, char* argv[])
{
	trans_t *vett_trans=NULL;
	trans_t *more_vett_trans=NULL;
	trans_t *temp=NULL;
	vett_trans=(trans_t*)malloc(25*63*sizeof(trans_t));
	long max;
	char *s;
	int a,e;			//caratteri transizioni
	char b,c,d;
	int i,j;			//indici vett_trans
	int numStati=25;	
	char c1,c2,c3;		//caratteri a c c
	acc_t * acc=NULL;	//lista acc
	//int A;				//stato di accettazione
	char *stringa;	//nastro e carattere
	char fine, fine2;
	statePosCurr_t *spc=NULL,*p,*listaT=NULL;
	acc_t* temp3;
	trans_t* temp4;
	char **vStr;
	char vuoto;
	int len;
	int x;
	trans_t* temp5;
	statePosCurr_t* p2;
	statePosCurr_t* list;
	
	
	
	
	s=(char*)malloc(sizeof(char)*20);					
	for(i=0;i<63;i++)
		for(j=0;j<25;j++){
			(*(vett_trans+i+j*63)).stateO=-1;
			(*(vett_trans+i+j*63)).next=NULL;

		}
	s=fgets(s, 4, stdin);		
	s=fgets(s, 20, stdin);
	
	sscanf( s, "%c %c %c", &c1, &c2, &c3);
	
	while(c1!='a' || c2!='c' || c3!='c'){
		sscanf( s, "%d %c %c %c %d", &a, &b, &c, &d, &e);
		if(a>=numStati){
			vett_trans=(trans_t*)realloc(vett_trans,(a+1)*63*sizeof(trans_t));
			for(i=0;i<63;i++)
				for(j=numStati;j<a+1;j++){
					(*(vett_trans+i+j*63)).stateO=-1;
					(*(vett_trans+i+j*63)).next=NULL;
				}
			numStati=a+1;
		}
		if(b>='a' && b<='z')
			temp=(vett_trans+a*63+b-48-7-4-1);
		else if(b=='_')
			temp=(vett_trans+a*63+b-48-7-4);
		else if(b>='A' && b<='Z')
			temp=(vett_trans+a*63+b-48-7);
		else if(b>='0' && b<='9')
			temp=(vett_trans+a*63+b-48);

		if((*temp).stateO==-1)
		{
			(*temp).w=c;
			(*temp).m=d;
			(*temp).stateO=e;
			(*temp).primo='1';
		}
		else{
			
			temp=inscoda(temp,c,d,e);
		}
		
		s=fgets(s, 20, stdin);
		sscanf( s, "%c %c %c", &c1, &c2, &c3);

	}
	
	
	
				
	//legge lista acc
	s=fgets(s, 20, stdin);
	
	sscanf( s, "%d", &a);
	sscanf( s, "%c %c %c", &c1, &c2, &c3);
	while(c1!='m' || c2!='a' || c3!='x')
	{
		acc=instestaAcc(acc,a);
		s=fgets(s, 20, stdin);
		sscanf( s, "%c %c %c", &c1, &c2, &c3);
		sscanf( s, "%d", &a);
	}
	
	s=fgets(s, 20, stdin);		//legge il max
	sscanf( s, "%ld", &max);
	
	s=fgets(s, 20, stdin);		//legge "run"
	
	free(s);
	int buffer;
	
	scanf("%ms",&stringa);
		
	
	long moveCurr=0;
	
	
		
	do{	
		if(strlen(stringa)>max)
		{	
			
			buffer=max+2;
		}
		//esecuzione
		else
			buffer=strlen(stringa)+1;
		fine='0';
		fine2='0';
		spc=NULL;
		listaT=NULL;
		vStr=(char**)malloc(sizeof(char*));
		*vStr=(char*)malloc((buffer)*sizeof(char));

		memcpy(*vStr, stringa,buffer);
		*(*vStr+buffer-1)='\0';

		free(stringa);
		spc=inscodaSPC(spc,*vStr,0,0,buffer);			
		vuoto='0';
		x=2;
		
		while(moveCurr<max && fine=='0')		
		{	moveCurr++;
			
			if (vuoto=='0')
			{
				for(p=spc;p && fine=='0';p=listaT)
				{

				
					if((*p).stateC>=numStati)
					{

							for(temp3=acc;temp3 && fine=='0';temp3=(*temp3).next2)		//controllo accettazione
							if((*p).stateC==(*temp3).s){
								fine='1';	
								list=NULL;
								for(p=spc;p ;p=list)
								{
									free((*p).stringa2);
									list=(*p).next;
									free(p);
									
								}
								vuoto='1';
							}
						if(fine!='1'){
							free((*p).stringa2);
							if(p==spc)
								{
									spc=(*spc).next;
								}
							listaT=eliminaElSpc(p, &vuoto);			
						
						}
					}
					else
					{
						if(*((*p).stringa2+(*p).indice)!='@' && *((*p).stringa2+(*p).indice)!='#' && *((*p).stringa2+(*p).indice)<='z' && *((*p).stringa2+(*p).indice)>='a')
							temp4=(vett_trans+*((*p).stringa2+(*p).indice)+63*(*p).stateC-48-7-4-1);	
						else if(*((*p).stringa2+(*p).indice)!='@' && *((*p).stringa2+(*p).indice)!='#' && *((*p).stringa2+(*p).indice)=='_')
							temp4=(vett_trans+*((*p).stringa2+(*p).indice)+63*(*p).stateC-48-7-4);	
						else if(*((*p).stringa2+(*p).indice)!='@' && *((*p).stringa2+(*p).indice)!='#' && *((*p).stringa2+(*p).indice)<='9' && *((*p).stringa2+(*p).indice)>='0')
							temp4=(vett_trans+*((*p).stringa2+(*p).indice)+63*(*p).stateC-48);	
						else if(*((*p).stringa2+(*p).indice)!='@' && *((*p).stringa2+(*p).indice)!='#' && *((*p).stringa2+(*p).indice)<='Z' && *((*p).stringa2+(*p).indice)>='A')
							temp4=(vett_trans+*((*p).stringa2+(*p).indice)+63*(*p).stateC-48-7);	
						
						else
							temp4=(vett_trans+'_'+63*(*p).stateC-48-7-4);
							
						
							
						if((*temp4).stateO==-1)		//no trans
						{
							for(temp3=acc;temp3 && fine=='0';temp3=(*temp3).next2){		//controllo accettazione
							
								
								if((*p).stateC==(*temp3).s){
									fine='1';	
									list=NULL;
									for(p=spc;p ;p=list)
									{
										free((*p).stringa2);
										list=(*p).next;
										free(p);
										
									}
									vuoto='1';
								}
							}
							if(fine!='1')
							{
								free((*p).stringa2);
								if(p==spc)
								{
									spc=(*spc).next;
								}
								listaT=eliminaElSpc(p, &vuoto);			
								
							}
						}
						
						else if((*temp4).primo=='1' && (*temp4).next==NULL)		//una trans
						{
							if((*p).stateC==(*temp4).stateO && (*((*p).stringa2+(*p).indice)==(*temp4).w || (*((*p).stringa2+(*p).indice)=='@' && (*temp4).w=='_') || (*((*p).stringa2+(*p).indice)=='#' && (*temp4).w=='_'))&& (*temp4).m=='S')
							{
								free((*p).stringa2);
								if(p==spc)
								{
									spc=(*spc).next;
								}
								listaT=eliminaElSpc(p, &vuoto);
								fine2='1';
							}
							else
							{
									(*p).stateC=(*temp4).stateO;
									*((*p).stringa2+(*p).indice)=(*temp4).w;
									if((*p).indice==0 && (*temp4).m=='L')
									{
										if((*p).lungh>=10)
										{
											(*p).stringa2=(char*)realloc((*p).stringa2,sizeof(char)*1.1*((*p).lungh));
											memmove((*p).stringa2+(int)(((*p).lungh)*0.1),(*p).stringa2,sizeof(char)*((*p).lungh));
											for(len=0;len<(int)(((*p).lungh)*0.1);len++)
												*((*p).stringa2+len)='@';
											
											(*p).indice=((*p).lungh)*0.1;
											(*p).lungh=(*p).lungh*1.1;
											
										}
										else
											{
												(*p).stringa2=(char*)realloc((*p).stringa2,sizeof(char)*((*p).lungh+1));
												memmove((*p).stringa2+1,(*p).stringa2,sizeof(char)*((*p).lungh));
												
												*((*p).stringa2)='@';
												
												(*p).indice=1;
												(*p).lungh=(*p).lungh+1;
											}									}
									else if(*((*p).stringa2+(*p).indice+1)=='\0' && (*temp4).m=='R')
									{
										if((*p).lungh>=10)										
										{
											(*p).stringa2=(char*)realloc((*p).stringa2,sizeof(char)*1.1*((*p).lungh));
										for(len=(*p).lungh-1;len<(int)(1.1*((*p).lungh)-1);len++)
											*((*p).stringa2+len)='#';
										(*p).lungh=(*p).lungh*1.1;
										*((*p).stringa2+(*p).lungh-1)='\0';
										
										}
										else											
										{
											(*p).stringa2=(char*)realloc((*p).stringa2,sizeof(char)*((*p).lungh+1));
											
											*((*p).stringa2+(*p).lungh-1)='#';
											(*p).lungh=(*p).lungh+1;
											*((*p).stringa2+(*p).lungh-1)='\0';
										}
									}
									
									if((*temp4).m=='L')
										(*p).indice=(*p).indice-1;
									else if((*temp4).m=='R')
										(*p).indice=(*p).indice+1;
									
									
																		
									listaT=(*p).next;
								
								
							}
						}
						
						else		//più trans
						{
							
							temp5=NULL;
							
							
							p2=p;
							for(temp5=(*temp4).next;temp5;temp5=(*temp5).next)
							{
								vStr=(char**)realloc(vStr, x*sizeof(char*));
								*(vStr+x-1)=(char*)malloc((*p).lungh*sizeof(char));
								
								memcpy(*(vStr+x-1), (*p).stringa2, (*p).lungh);	
								p2=insMezzoSPC(p2,*(vStr+x-1),(*temp5).stateO,(*p).indice,(*p).lungh);	
								p2=(*p2).next;
								x++;
								*((*p2).stringa2+(*p2).indice)=(*temp5).w;
								
								if((*p2).indice==0 && (*temp5).m=='L')
								{
									if((*p).lungh>10)
									{
										(*p2).stringa2=(char*)realloc((*p2).stringa2,sizeof(char)*1.1*((*p2).lungh));
										memmove((*p2).stringa2+(int)(((*p2).lungh)*0.1),(*p2).stringa2,sizeof(char)*((*p2).lungh));
										for(len=0;len<(int)(((*p2).lungh)*0.1);len++)
											*((*p2).stringa2+len)='@';
										(*p2).indice=((*p2).lungh)*0.1;
										(*p2).lungh=(*p2).lungh*1.1;
									}
									else
									{
										(*p2).stringa2=(char*)realloc((*p2).stringa2,sizeof(char)*((*p2).lungh+1));
										memmove((*p2).stringa2+1,(*p2).stringa2,sizeof(char)*((*p2).lungh));
										*((*p2).stringa2)='@';
										(*p2).indice=1;
										(*p2).lungh=(*p2).lungh+1;
									}
								}
								else if(*((*p2).stringa2+(*p2).indice+1)=='\0' && (*temp5).m=='R')
								{
									if((*p).lungh>=10)
									{
									(*p2).stringa2=(char*)realloc((*p2).stringa2,sizeof(char)*1.1*(*p2).lungh);
									for(len=(*p2).lungh-1;len<(int)(1.1*(*p2).lungh-1);len++)
										*((*p2).stringa2+len)='#';
									(*p2).lungh=(*p).lungh*1.1;
									*((*p2).stringa2+(*p2).lungh-1)='\0';
									}
									else
									{
										(*p2).stringa2=(char*)realloc((*p2).stringa2,sizeof(char)*((*p2).lungh+1));
										
											*((*p2).stringa2+(*p2).lungh-1)='#';
										(*p2).lungh=(*p).lungh+1;
										*((*p2).stringa2+(*p2).lungh-1)='\0';
									}								
								}
								if((*temp5).m=='L')
									(*p2).indice=(*p2).indice-1;
								else if((*temp5).m=='R')
									(*p2).indice=(*p2).indice+1;
							}
							
							(*p).stateC=(*temp4).stateO;
							*((*p).stringa2+(*p).indice)=(*temp4).w;
							if((*p).indice==0 && (*temp4).m=='L')
							{
								if((*p).lungh>=10)
								{
									(*p).stringa2=(char*)realloc((*p).stringa2,sizeof(char)*1.1*((*p).lungh));
									memmove((*p).stringa2+(int)(((*p).lungh)*0.1),(*p).stringa2,sizeof(char)*((*p).lungh));
									for(len=0;len<(int)(((*p).lungh)*0.1);len++)
										*((*p).stringa2+len)='@';
											
									(*p).indice=((*p).lungh)*0.1;
									(*p).lungh=(*p).lungh*1.1;
								
								}
								else
								{
									(*p).stringa2=(char*)realloc((*p).stringa2,sizeof(char)*((*p).lungh+1));
									memmove((*p).stringa2+1,(*p).stringa2,sizeof(char)*((*p).lungh));
									
										*((*p).stringa2+1)='@';
											
									(*p).indice=1;
									(*p).lungh=(*p).lungh+1;
								}	
							}
							else if(*((*p).stringa2+(*p).indice+1)=='\0' && (*temp4).m=='R')
							{
								if((*p).lungh)
								{
									(*p).stringa2=(char*)realloc((*p).stringa2,sizeof(char)*1.1*(*p).lungh);
									for(len=(*p).lungh-1;len<(int)(1.1*(*p).lungh-1);len++)
										*((*p).stringa2+len)='#';
									(*p).lungh=(*p).lungh*1.1;
									*((*p).stringa2+(*p).lungh-1)='\0';
								}
								else
								{
									(*p).stringa2=(char*)realloc((*p).stringa2,sizeof(char)*((*p).lungh+1));
									
									*((*p).stringa2+(*p).lungh-1)='#';
									(*p).lungh=(*p).lungh+1;
									*((*p).stringa2+(*p).lungh-1)='\0';
								}							
							}
									
							if((*temp4).m=='L')
								(*p).indice=(*p).indice-1;
							else if((*temp4).m=='R')
								(*p).indice=(*p).indice+1;	
								
							listaT=(*p2).next;
						}
					}
					
				}
			}
			else 
				fine='2';
		}

		if(moveCurr==max && vuoto=='0'){
			listaT=NULL;
			for(p=spc; p && fine=='0'; p=listaT)
				for(temp3=acc;temp3 && fine=='0';temp3=(*temp3).next2){
					if((*p).stateC==(*temp3).s)
					{
						fine='1';	
						list=NULL;
						for(p=spc;p ;p=list)
						{
							free((*p).stringa2);
							list=(*p).next;
							free(p);
							vuoto='1';
						}	
						listaT=NULL;
					}
					else
						listaT=(*p).next;
				}
		}
		
		
		for(p=spc;p && vuoto=='0';p=list)
		{
			free((*p).stringa2);
			list=(*p).next;
			free(p);
			
		}
		free(vStr);
		
		
		if(fine=='1')
			fprintf(stdout, "1\n");
		else if(fine2=='1' || moveCurr>=max)
			fprintf(stdout, "U\n");
		else if(moveCurr<max)
			fprintf(stdout, "0\n");
		list=NULL;

		
		moveCurr=0;
		

	}while(scanf("%ms",&stringa)!=EOF);	

	free(vett_trans);


	
	return 0;
}


trans_t* inscoda(trans_t* h, char c,char d, int e)
	{
		trans_t *nuovo;
		
		if(h==NULL) {
    		h=(trans_t *)malloc(sizeof(trans_t));
    		(*h).w=c;
			(*h).m=d;
			(*h).stateO=e;
			(*h).primo='1';
			(*h).next=NULL;
    		return h;
		  }
		nuovo=h;
		while((*nuovo).next!=NULL)
			nuovo=(*nuovo).next;
		(*nuovo).next=(trans_t *)malloc(sizeof(trans_t));
		nuovo=(*nuovo).next;
		(*nuovo).w=c;
		(*nuovo).m=d;
		(*nuovo).stateO=e;
		(*nuovo).primo='0';
		(*nuovo).next=NULL;
		return h;
	}
	
acc_t* instestaAcc(acc_t *h, int dato)
{
	acc_t *nuovo=NULL;
	if((nuovo=(acc_t *)malloc(sizeof(acc_t))))
			{
				(*nuovo).s=dato;				
				(*nuovo).next2=h;
				h=nuovo;
			}
		else
			printf("errore memoria");
		return h;
}

statePosCurr_t* inscodaSPC(statePosCurr_t *h, char* str, int stato,int ind, int L)
{
	statePosCurr_t *nuovo=NULL,*testa;
	if(h==NULL)
	{
		h=(statePosCurr_t *)calloc(1,sizeof(statePosCurr_t));
		(*h).stringa2=str;
		(*h).stateC=stato;
		(*h).indice=ind;
		(*h).lungh=L;		
		(*h).prev=NULL;
		testa=h;
	}
	else
	{
		testa=h;
		while((*h).next!=NULL)
			h=(*h).next;
		nuovo=(statePosCurr_t *)calloc(1,sizeof(statePosCurr_t));
		
		(*nuovo).stringa2=str;				
		(*nuovo).stateC=stato;	
		(*nuovo).indice=ind;
		(*nuovo).lungh=L;		
		(*nuovo).next=NULL;
		(*nuovo).prev=h;				
			
	}
	(*h).next=nuovo;

	return testa;
}

statePosCurr_t* eliminaElSpc(statePosCurr_t* h, char* v)
{
	statePosCurr_t* l=NULL;
	l=h;
	if((*l).next==NULL && (*l).prev==NULL)
	{
		free(h);
		*v='1';
		return NULL;
	}
	else if((*h).next==NULL)
	{
		(*((*h).prev)).next=NULL;
		free(h);
		return NULL;		
	}
	else if((*h).prev==NULL)
	{
		h=(*h).next;
		(*h).prev=NULL;
		free(l);
		return h;
	}
	else 
	{
		h=(*h).next;
		(*h).prev=(*l).prev;
		(*((*l).prev)).next=(*l).next;
		free(l);
		return h;
	}
		
	
}

statePosCurr_t* insMezzoSPC(statePosCurr_t* h , char* str, int stato, int ind ,int L)
{
		statePosCurr_t *nuovo=NULL,*p;
		nuovo=(statePosCurr_t *)calloc(1,sizeof(statePosCurr_t));
		(*nuovo).stringa2=str;				
		(*nuovo).stateC=stato;	
		(*nuovo).indice=ind;
		(*nuovo).lungh=L;	
		(*nuovo).next=(*h).next;
		(*nuovo).prev=h;				

		p=h;
		if((*p).next)
			(*((*p).next)).prev=nuovo;
		(*h).next=nuovo;
		return h;
}
