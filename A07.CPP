#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

int n;
vector<vector<int>> C;
vector<int> x, tot_nhat;
vector<bool> tham;
int ky_luc = INT_MAX;
int c_min = INT_MAX;
long long so_nut_da_duyet = 0;

// Ham tim canh co trong so nho nhat ngoai duong cheo chinh
int tim_canh_nho_nhat(const vector<vector<int>>& mat) {
    int min_val = INT_MAX;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j && mat[i][j] < min_val) {
                min_val = mat[i][j];
            }
        }
    }
    return min_val;
}

// Ham de quy nhanh va can don gian
void thu_hanh_trinh(int k, int chi_phi_hien_tai) {
    so_nut_da_duyet++;

    if (k == n) {
        int u = x[n - 1];
        if (C[u][0] > 0) {
            int tong_chi_phi = chi_phi_hien_tai + C[u][0];
            if (tong_chi_phi < ky_luc) {
                ky_luc = tong_chi_phi;
                tot_nhat = x;
                tot_nhat.push_back(0);
            }
        }
        return;
    }

    for (int j = 0; j < n; ++j) {
        if (!tham[j]) {
            int u = x[k - 1];
            int chi_phi_moi = chi_phi_hien_tai + C[u][j];
            int can_duoi = chi_phi_moi + (n - k) * c_min;

            if (can_duoi < ky_luc) {
                tham[j] = true;
                x[k] = j;
                thu_hanh_trinh(k + 1, chi_phi_moi);
                tham[j] = false;
            }
        }
    }
}

// Ham kiem tra tinh hop le cua mot hanh trinh
bool kiem_tra_hanh_trinh(const vector<vector<int>>& mat, const vector<int>& duong) {
    int m = (int)mat.size();
    if ((int)duong.size() != m + 1) return false;
    if (duong[0] != 0 || duong[m] != 0) return false;

    vector<bool> da_di(m, false);
    for (int i = 0; i < m; ++i) {
        int u = duong[i];
        int v = duong[i + 1];
        if (u < 0 || u >= m || v < 0 || v >= m) return false;
        if (da_di[u]) return false; // Phat hien dinh trung lap (vi du [1, 2, 2, 1])
        if (mat[u][v] <= 0) return false; // Khong co duong di truc tiep
        da_di[u] = true;
    }
    return true;
}