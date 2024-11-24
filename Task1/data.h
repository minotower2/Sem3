# ifndef data_H
# define data_H
# define LEN 1234 
# include <stdio.h>
# include <sstream>
# include <string>
#include "returns.h"

class data
{
	private:
		int m = M;
		double a[M] = {0};
		static int p;
	public:
		data () = default;
		~data () = default;
		int get_m () const { return m; }
		const double * get_a () { return a; }
		static int get_p () { return p; }
		static void set_p (int q){ p = q; }
		// Copy constructor
		data (const data &x) = default;
		// Assignement operator
		data& operator= (const data&) = default;
		// Comparison operators
		int operator< (const data& x) const { return m < x.m; }
		int operator> (const data& x) const { return m > x.m; }
		// Print data in a line (not more than p): m a[0] a[1] ... a[m-1]
		void print (FILE * fp = stdout){
			int len = get_m(), i;
			len = p < len ? p : len;
			fprintf(fp, "%d", m);
			for (i = 0; i < len; i++)
				fprintf(fp, " %le", a[i]);
			fprintf(fp, "\n");
		}
		// Read data from the line: m a[0] a[1] ... a[m-1]
		int read (FILE *fp = stdin) {
			char buf[LEN];
		      	int m_, i;
		        std::string str;
		      	if (!(fgets(buf, LEN, fp))) {
				return 1;
		      	}
		      	for(i = 0; buf[i]; ++i) {
				if(buf[i] == '\n') {
			  	buf[i] = 0;
			  	break;
				}
		      	}
			      	str = buf;
			      	std::stringstream s(str);
			      	if(!(s >> m_)) {
					return 1;
			      	}
			      	m = (m_ > M ? M : m_);
			      	for (i = 0; i < m; i++) {
					if(!(s >> a[i])) {
				 	 	return 1;
					}
			      	}
			      	return 0;
		}
		// Init data by formulae with number s
		void init (int s) {
			int m_ = (m < M ? m : M);	
			m = s;
			a[m_] = {0};
		}
};
# endif // dat
