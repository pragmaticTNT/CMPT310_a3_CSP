
const int MAXSTRING = 100;

typedef long clock_t;
typedef long time_t;

class TIME_KEEPER
{
public: 
  void start_time(void);
  double print_time(void);
    

private:
  clock_t  begin_clock, save_clock;
  time_t   begin_time,  save_time;
};

void TIME_KEEPER::start_time(void)
{
  begin_clock = save_clock = clock();
  begin_time  = save_time  = time(NULL);
}

double TIME_KEEPER::print_time(void)
{
  char s1[MAXSTRING], s2[MAXSTRING];
  int field_width, n1, n2;
  double clocks_per_second = (double) CLOCKS_PER_SEC,
         user_time, real_time;

  user_time  = (clock() - save_clock) / clocks_per_second;
  real_time  = difftime(time(NULL), save_time);
  save_clock = clock();
  save_time  = time(NULL);

  // print the user_time and the real_time;

  n1 = sprintf(s1, "%.1f", user_time);
  n2 = sprintf(s2, "%.1f", real_time);
  field_width = (n1 > n2) ? n1 : n2;
  printf("%s%*.1f%s\n%s%*.1f%s\n\n",
	 "  User time: ", field_width, user_time, " seconds",
	 "  Real time: ", field_width, real_time, " seconds");
 
  return(user_time);
}
