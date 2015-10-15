#include <iostream>
#include <algorithm>
#include <string>
#include <vector>


int lcs(std::string &X, std::string &Y)
{
      using namespace std;
      const int m = X.size();
      const int n = Y.size();
      const int stride = m + 1;
      vector<int> L((m + 1)*(n + 1), 0);


      for (int i = 0; i<=m; i++)
	    {
              for (int j = 0; j<=n; j++)
	          {
	            if (i == 0 || j == 0)
	                    L[i*stride + j] = 0;
                  else if (X[i - 1] == Y[j - 1])
	                L[i*stride + j] = L[(i - 1)*stride + j - 1] + 1;
            else
	                L[i*stride + j] = max(L[(i - 1)*stride + j], L[i*stride + j - 1]);
              }
     }
      return L[m*stride + n];

}

int main()
{
      using namespace std;
      string X{ "AGGTAB" };
      string Y{"GXTXAYB"};

      cout << lcs(X, Y);
      return 0;
}
