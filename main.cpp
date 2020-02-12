#include <stdio.h>
#include <stdlib.h>
#include <time.h>


unsigned long DiffTime(struct timespec& start_time, struct timespec& end_time)
{
  struct timespec diff_time;
  unsigned long lRet = 0;
	
  printf("開始時刻　 = %10ld.%09ld\n", start_time.tv_sec, start_time.tv_nsec);
  printf("終了時刻　 = %10ld.%09ld\n", end_time.tv_sec, end_time.tv_nsec);
  printf("経過実時間 = ");
  if (end_time.tv_nsec < start_time.tv_nsec) {
    printf("%10ld.%09ld", end_time.tv_sec - start_time.tv_sec - 1
          ,end_time.tv_nsec + 1000000000 - start_time.tv_nsec);
    diff_time.tv_sec = end_time.tv_sec - start_time.tv_sec - 1;
    diff_time.tv_nsec = end_time.tv_nsec + 1000000000 - start_time.tv_nsec;
          
  } else {
    printf("%10ld.%09ld", end_time.tv_sec - start_time.tv_sec
          ,end_time.tv_nsec - start_time.tv_nsec);
    diff_time.tv_sec = end_time.tv_sec - start_time.tv_sec;
    diff_time.tv_nsec = end_time.tv_nsec - start_time.tv_nsec;

  }
  printf("(秒)\n");	
  
  lRet = diff_time.tv_sec * 1000;
  lRet += diff_time.tv_nsec / (1000 * 1000);
  
  return lRet;
}



int main(void)
{
	struct timespec				start_time;
	struct timespec				end_time;
	struct timespec				sleep_time;
	
	
	// 処理開始時間を取得
	clock_gettime(CLOCK_MONOTONIC_RAW, &start_time);
	
	// 時間がかかる処理を実行
	sleep_time.tv_sec = 0;
	sleep_time.tv_nsec = 525 * 1000 * 1000;
	nanosleep(&sleep_time, NULL);
	
	// 処理終了時間を取得
	clock_gettime(CLOCK_MONOTONIC_RAW, &end_time);

	// 処理時間を計測
	unsigned long ms = DiffTime(start_time,end_time);
	printf("%u ms\n",ms);
	
	
	return 0;
}
