/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elman <elman@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 18:23:20 by elman             #+#    #+#             */
/*   Updated: 2021/11/21 22:54:39 by elman            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
int main()
{
	int i = 0; 

	int pid = 0;

	while(i < 10)
	{
		if (fork() == 0)
		{
			// pid = fork();
			printf("PID %d, Parent Pid: %d \n", pid, getppid());
			exit(0);
		}
		
		i++;
	}
	// for(int i=0;i<5;i++) // loop will run n times (n=5)
    // {
    //     if(fork() == 0)
    //     {
    //         printf("[son] pid %d from [parent] pid %d\n",getpid(),getppid());
    //         exit(0);
    //     }
    // }
    // for(int i=0;i<5;i++) // loop will run n times (n=5)
	wait(NULL);
		
}