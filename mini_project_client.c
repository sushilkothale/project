#include"header.h"
int main(int argc,char **argv)
{
	if(argc!=3)	
	{
	printf("Usage:./c portnum ipaddress\n");
	return 0;
	}
	char s[]="Welcome",device_name[20];
	struct sockaddr_in v;
	int sfd,len,i,id,pid;

	/*create socket file*/
	sfd=socket(AF_INET,SOCK_DGRAM,0);
	if(sfd<0)
	{
		perror("socket");
		return 0;
	}
	perror("socket");

	v.sin_family=AF_INET;
	v.sin_port=htons(atoi(argv[1]));
	v.sin_addr.s_addr=inet_addr(argv[2]);
	len=sizeof(v);
	sendto(sfd,s,strlen(s)+1,0,(struct sockaddr*)&v,len);
	while(1)
	{
		recvfrom(sfd,&i,sizeof(i),0,(struct sockaddr*)&v,&len);
		printf("i=%d\n",i);
		switch(i)
		{
			case 1:
				printf("Enter Device ID\n");
			       	scanf("%d",&id);
			       	sendto(sfd,&id,sizeof(id),0,(struct sockaddr*)&v,len);
			       	break;
			case 2:
				printf("Enter Device Name\n");
			       	scanf(" %[^\n]",device_name);
				sendto(sfd,device_name,strlen(device_name)+1,0,(struct sockaddr*)&v,len);
			       	break;
			case 3:
				pid=getpid();
			       	sendto(sfd,&pid,sizeof(pid),0,(struct sockaddr*)&v,len);
			       	break;
		}
		if(i>=4)
			break;
	}
}	
