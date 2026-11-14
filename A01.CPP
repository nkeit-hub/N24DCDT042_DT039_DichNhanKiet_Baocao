#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

// === KHAI BÁO BIẾN TOÀN CỤC ===
int n;
vector<vector<int>> C;
vector<int> x, tot_nhat;
vector<bool> tham;
int ky_luc = INT_MAX;
int c_min = INT_MAX;
long long so_nut_da_duyet = 0;

// === HÀM TÌM CẠNH NHỎ NHẤT ===
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

// === HÀM ĐỆ QUY NHÁNH VÀ CẬN ===
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

// === HÀM XÁC THỰC ĐẦU VÀO ===
bool kiem_tra_dau_vao(int n_val, const vector<vector<int>>& mat) {
    if (n_val < 2 || n_val > 9) {
        cout << "[LOI] So luong thanh pho n phai nam trong doan [2, 9]!\n";
        return false;
    }
    for (int i = 0; i < n_val; ++i) {
        if (mat[i][i] != 0) {
            cout << "[LOI] Chi phi duong cheo C[" << i+1 << "][" << i+1 << "] phai bang 0!\n";
            return false;
        }
        for (int j = 0; j < n_val; ++j) {
            if (i != j && mat[i][j] <= 0) {
                cout << "[LOI] Trong so C[" << i+1 << "][" << j+1 << "] phai la so nguyen duong!\n";
                return false;
            }
        }
    }
    return true;
}

// === HÀM CHÍNH (MAIN) ===
int main() {
    cout << "=== CHUONG TRINH TSP NHANH VA CAN DON GIANG (DT039) ===\n";
    cout << "Nhap so thanh pho n: ";
    if (!(cin >> n)) return 0;

    C.assign(n, vector<int>(n));
    cout << "Nhap ma tran chi phi C (" << n << "x" << n << "):\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> C[i][j];
        }
    }

    if (!kiem_tra_dau_vao(n, C)) return 1;

    c_min = tim_canh_nho_nhat(C);
    x.resize(n);
    tham.assign(n, false);
    x[0] = 0;
    tham[0] = true;
    ky_luc = INT_MAX;
    so_nut_da_duyet = 0;

    thu_hanh_trinh(1, 0);

    if (ky_luc == INT_MAX) {
        cout << "\nKhong tim thay hanh trinh hop le!\n";
    } else {
        cout << "\n=== KET QUA OPTIMAL ===\n";
        cout << "Chi phi nho nhat (chi_phi): " << ky_luc << "\n";
        cout << "Hanh trinh (hanh_trinh): [";
        for (int i = 0; i < (int)tot_nhat.size(); ++i) {
            cout << tot_nhat[i] + 1;
            if (i + 1 < (int)tot_nhat.size()) cout << ", ";
        }
        cout << "]\n";
        cout << "Tong so nut da duyet: " << so_nut_da_duyet << "\n";
    }

    return 0;
}