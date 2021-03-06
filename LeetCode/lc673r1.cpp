// O(n log n) LIS + O(n) extension, achieved 4ms running time.

vector<int> s[2100];
vector<int> ss[2100];
int n, c[2100], l[2100], b[2100];


vector<int> longest;

int bs(vector<int> &t, int x) {
    int n = t.size();
    int beg = 0, end = n, mid;
    while(beg < end) {
        mid = (beg + end) / 2;
        if(t[mid] < x) {
            beg = mid + 1;
        } else {
            end = mid;
        }
    }
    return end;
}

void print(vector<int> &t) {
    for(int i = 0; i < t.size(); ++i) {
        cout << t[i] << ' ';
    }
    cout << endl;
}

int bs2(vector<int> &t, int x) {
    int n = t.size();
    int beg = 0, end = n, mid;
    while(beg < end) {
        mid = (beg + end) / 2;
        if(t[mid] >= x) {
            beg = mid + 1;
        } else {
            end = mid;
        }
    }
    return end;
}

int bs3(int k, int x) {
    vector<int> &t = s[k];
    int i, n = t.size();
    for(i = b[k]; i < n; ++i) {
        if(t[i] < x) break;
    }
    b[k] = i;
    return i;
}


class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        n = nums.size();
        longest.clear();
        for(int i = 0; i <= n; ++i) {
            s[i].clear();
            ss[i].clear();
            ss[i].push_back(0);
            b[i] = 0;
        }
        for(int i = 0; i < n; ++i) {
            int tmp = bs(longest, nums[i]);
            if(tmp >= longest.size()) {
                longest.push_back(nums[i]);
            } else {
                if(longest[tmp] > nums[i]) {
                    longest[tmp] = nums[i];
                }
            }
            l[i] = tmp;
            
            
            if(tmp == 0) {
                c[i] = 1;
            } else {
                //print(s[tmp-1]);
                //cout << "bs2 " << nums[i] << " " << bs2(s[tmp-1], nums[i]) << " " << bs3(tmp-1, nums[i]) << endl;           
                //int ssr = bs2(s[tmp-1], nums[i]);
                int ssr = bs3(tmp-1, nums[i]);
                c[i] = ss[tmp-1].back() - ss[tmp-1][ssr];
            }
                        
            s[tmp].push_back(nums[i]);
            ss[tmp].push_back(ss[tmp].back() + c[i]);

        }
        //print(longest);
        int m = longest.size() - 1;
        int ans = 0;
        for(int i = 0; i < n; ++i) {
            //cout << '(' << l[i] << ',' << c[i] << ')';
            if(l[i] == m) {
                ans += c[i];
            }
        }
        return ans;
    }
};
