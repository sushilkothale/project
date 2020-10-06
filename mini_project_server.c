#include"header.h"
int main(int argc,char **argv)
{
	if(argc!=3)
	{
		printf("Usage:./s portnum ipaddress\n");
		return 0;
	}
	char s[150],device_name[20];
	struct sockaddr_in v,v1;
	int sfd,len,b,i,id,pid;

	/*create the socket*/
	sfd=socket(AF_INET,SOCK_DGRAM,0);
	if(sfd<0)
	{
		perror("socket");
		return 0;
	}
	perror("socket");

	/*Binding the data*/
	v.sin_family=AF_INET;
	v.sin_port=htons(atoi(argv[1]));
	v.sin_addr.s_addr=inet_addr(argv[2]);
	len=sizeof(v);
	b=bind(sfd,(struct sockaddr*)&v,len);
	if(b<0)
	{
		perror("Bind");
		return 0;
	}
	perror("Bind");

	/*send and receive data*/
	recvfrom(sfd,s,sizeof(s),0,(struct sockaddr*)&v1,&len);
	printf("data=%s\n",s);
	printf("1)Device ID 2)Device Name 3)Process ID\n");
	while(1)
	{
		printf("Enter option\n");
		scanf("%d",&i);
		switch(i)
		{
			case 1:
				sendto(sfd,&i,sizeof(i),0,(struct sockaddr*)&v1,len);
				recvfrom(sfd,&id,sizeof(id),0,(struct sockaddr*)&v1,&len);
				printf("Device ID=%d\n",id);
				break;
			case 2:
				sendto(sfd,&i,sizeof(i),0,(struct sockaddr*)&v1,len);
				recvfrom(sfd,device_name,sizeof(device_name),0,(struct sockaddr*)&v1,&len);
				printf("Device Name=%s\n",device_name);
				break;
			case 3:
				sendto(sfd,&i,sizeof(i),0,(struct sockaddr*)&v1,len);
				recvfrom(sfd,&pid,sizeof(pid),0,(struct sockaddr*)&v1,&len);
				printf("Process ID=%d\n",pid);
				break;
		}
		if(i>=4)
		{
			sendto(sfd,&i,sizeof(i),0,(struct sockaddr*)&v1,len);
			break;
		}
	}
}
