/*ʱ��ת��������ģ��1��**/
#include <stdio.h>
#define file1 "data.csv"
#define file2 "wave.txt"

int main(void)
{	
	FILE *fp1,*fp2,*fp3,*fp4,*fp5,*fp6,*fp;                         //������.xlsx�ļ��������Ϊ.csv�ļ�
	double DEPTH,AC,DEN,V,T = 1712;                                 //��ȣ�DEPTH��,����ʱ�AC��,�ܶȣ�DEN��,T�ĳ�ʼֵ
	double DEPTH_1 = 50.01,DEPTH_2,temp_1,temp_2,V_last;            //DEPTH_1��ʼֵ ,����ĳ�ֵ�ļ���һ�� ��Ҫ���� ������Ҫע��
	char line[50];                                                  //��ȡÿ��csv����
	int count = 1,temp = 0;
	char file[20];	
	char Y_N;
	int a,b,max,flag = 1711;
	double DEPTH_three, T_result_3, V_3, DEN_3,DEPTH_two, T_result_2, V_2, DEN_2, DEPTH_one, T_result_1, V_1, DEN_1;
	int i=1,L=25,N=0,n=1;                                                    // L�Ӳ�������n�������
	double num_Z[500], num_T[500],num_R[500],num_b[500],S = 0;


	
	
	printf("Your files are 'data.csv' and 'wave.t' (Y/N) ? \n");
	scanf("%c", &Y_N);
	if(Y_N=='n'||Y_N=='N'){
		printf("You can change them from program ...\n");
		getchar();
		return 0;
	}
	
	
/*************�������еõ�V************************************/
	fp1 = fopen(file1, "r");  	                               //��"ԭʼ����"�ļ�
	
		if(fp1==NULL) 
			printf("\n���ܴ� ������ ����ļ�");
	
	fp2 = fopen("new.csv", "w");	                               //��"V"�ļ�(�½�)
	
		if(fp2==NULL) 
			printf("\n���ܴ� new.csv ����ļ�");
	
	V_last = 1000000/186.2993;                                    //��һ��V��ֵ
	while(fgets(line, 50, fp1)){
		
		sscanf(line, "%lf,%lf,%lf\n", &DEPTH,&AC,&DEN);           //��ȡ����

		V = 1000000/AC;  	                                      //���Vֵ
		
		DEPTH_2 = DEPTH;
		T = T + 2000*(DEPTH_2-DEPTH_1)/V_last;                    //���Tֵ
	
	  //printf("#%d  DEPTH = %lf,AC = %lf,DEN = %lf, V = %lf, T = %lf\n", count,DEPTH,AC,DEN,V,T);
	  //count++;                                                        
	
		fprintf(fp2, "%lf,%lf,%lf,%lf \n",DEPTH,T,V,DEN);          //����
		V_last = V;
		DEPTH_1 = DEPTH_2;
  } 
    fclose(fp1);
	fclose(fp2);
		
/**************��T����ɸѡ**********************************/
	
	fp2 = fopen("new.csv", "r");                                   //��new�����ļ�
	if(fp2==NULL) printf("\n���ܴ� new ����ļ�");
	
	
	fp4 = fopen("new_T.csv", "w");                                 //ɸѡ�������ļ�
	if(fp4==NULL) printf("\n���ܴ� new_T.csv ����ļ�");
		
   	
	
	count = 1712;                                                  //һЩ��ʱ����

	
	while(fgets(line, 50, fp2)){                                   //ѭ��ɸѡ��������		 
		sscanf(line, "%lf,%lf,%lf,%lf\n", &DEPTH,&T,&V,&DEN);      //��ȡÿ������
		if((int)(T)==count)                                        //'����'����ܽӽ�ֵ  
			{
				if((int)(T*10000)%10000==0){
					
					fprintf(fp4, "%lf,%lf,%lf,%lf\n",DEPTH,T,V,DEN);//��ȡ��һ������
				}                                                    
			
				max = 0;
				if(max <= (int)((T - count)*100)){                 //��ǰ����󣬼���һ�������ܽӽ�ֵ
					max = (int)((T-count)*100);
					T_result_1 = T;                                //��ȡT
					DEPTH_one = DEPTH;                             //��ȡDEPTH
					V_1 = V;									   //��ȡV
					DEN_1 = DEN;                                   //��ȡDEN
			    }
           }
		else
			{                                                      //��һ����С
				T_result_3 = T;                                
				DEPTH_three = DEPTH;                             
				V_3 = V;									   
				DEN_3 = DEN; 
				count++;
			
		a = (int)((count - T_result_1)*1000000);                  //����ֵ1
		b = (int)((T_result_3 - count)*1000000);	              //����ֵ2
		
		if(a>=b)                                                  //ѡ��������Ϊnew_T.csv
			fprintf(fp4, "%lf,%lf,%lf,%lf \n",DEPTH_three,T_result_3,V_3,DEN_3);
		else
			fprintf(fp4, "%lf,%lf,%lf,%lf \n",DEPTH_one,T_result_1,V_1,DEN_1);
			}
			
 }
    fclose(fp2);
	fclose(fp4);

/************************�ٴθ���ɸѡ****************************************/

	fp3 = fopen("new_T_2.csv", "w"); 
	if(fp3==NULL) printf("\n���ܴ� new_T_2.csv ����ļ�");	  //T����ɸѡ�������ļ�
	
	fp4 = fopen("new_T.csv", "r");                                //T����ɸѡ�������ļ�
	if(fp4==NULL) printf("\n���ܴ� new_T.csv ����ļ�");        
	
	while(fgets(line, 50, fp4)){                                  //ѭ����������ϵ�
		
		flag++;
		sscanf(line, "%lf,%lf,%lf,%lf\n", &DEPTH,&T,&V,&DEN);
		if(flag%2==0){
			fprintf(fp3, "%lf,%d,%lf,%lf \n",DEPTH,flag,V,DEN);

		}
		
	}
	fclose(fp3);
	fclose(fp4);




/**************************���Z��R��ֵ�������********************************************/


/*�ϳɵ����¼������ģ��2��*/




fp = fopen("Z.txt", "w"); 
fp3 = fopen("new_T_2.csv", "r"); 
	while(fgets(line,500,fp3))                                          //��ȡnew_T_2.csv�ļ�
	{
		sscanf(line,"%lf,%lf,%lf,%lf", &DEPTH,&T,&V,&DEN);
		num_Z[i] = V * DEN;                                              //���Zֵ
		printf("Test Z[%d] = %lf\n", i,num_Z[i]);                       //���Դ��� ��ɾ��
		fprintf(fp,"Z[%d] = %lf\n", i,num_Z[i]); 
		num_T[i] = T;                                                   //����Tֵ
		i++;
		N = i-1;                                                        //Z�ĸ���N  114
		count = N;
	}
	fclose(fp3);
	fclose(fp);
	
	
fp = fopen("R.txt", "w"); 
for(i = 1; i<N; i++){
	num_R[i] = (num_Z[i+1]-num_Z[i])/(num_Z[i+1]+num_Z[i]);
	printf("Test R[%d] = %lf\n", i,num_R[i]);                       	//���Դ��� ��ɾ��
	fprintf(fp," R[%d] = %lf\n", i,num_R[i]);
	}                                                                   //��ȡR,����N 113
	N = N - 1;                                                         //R�ĸ��� ��Z��1
	fclose(fp);



/*****************************�õ��Ӳ�����******************************/
fp5=fopen(file2,"r");                                                 //��ȡ �Ӳ�
if(fp5==NULL) printf("\n���ܴ� �Ӳ� ����ļ�");

    for(i=1;i<=L;i++){
		fscanf(fp5,"%lf",&num_b[i]);
	    printf("Test b[%d] = %lf\n", i,num_b[i]);
	}
	fclose(fp5);
/**********************************************************************/

fp6 = fopen("new_S.txt", "w");                                     //д��S��¼
	for(n=1; n<=L+N; n++){
	
		for(i=1; i<=L; i++){                                      //L = 25
		
			if((n-i>0) && ((n-i) < N))
			S +=  (num_R[n - i]) * (num_b[i]); 
		
    
		}                                                      //���Ӵ�S[1]��S[25]
		                                                          //S(n)=
		//if(n>N)
			//S = 0;
		
		printf("S[%d] = %lf\n",n,S);
		fprintf(fp6,"S[%d] = %lf\n",n,S);
		S = 0;

}
	fclose(fp6);

	return 0;
}

/******************************************
1.�����Ѿ�ȫ��ʵ�� 
2.�����Ű���������Щ���ң�����Ҫ �������޸ġ�
3.�ļ�excel��C�����޷���ȡ�������Ϊcsv��ʽ�����ݲ���ı��
4.���ڲ��Դ��룬��Ҫ����ɾ��
5.��Ӧ�ļ������������޸�  
*******************************************/
