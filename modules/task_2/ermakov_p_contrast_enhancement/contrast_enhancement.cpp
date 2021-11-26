// Copyright 2021 Ermakov Pavel
#include "../../../modules/task_2/ermakov_p_contrast_enhancement/contrast_enhancement.h"

std::vector<std::vector<int>> pic_gen(int h, int w) {
    std::mt19937 rand_r(time(0));
    std::vector<std::vector<int>> m(h, std::vector<int>(w));
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            m[i][j] = rand_r() % 256;
        }
    }
    return m;
}

int barrier(int pixel) {
    if (pixel > 255)
        pixel = 255;
    if (pixel < 0)
        pixel = 0;
    return pixel;
}

std::vector<std::vector<int>> contrast_enhancement_seq(std::vector<std::vector<int>> pic, double alpha, int beta) {
    int rows = pic.size();
    int cols = pic[0].size();
    std::vector<std::vector<int>> tmp(rows, std::vector<int>(cols));
    for (int x = 0; x < rows; x++) {
        for (int y = 0; y < cols; y++) {
            tmp[x][y] = barrier(alpha * pic[x][y] + beta);
        }
    }
    return tmp;
}

std::vector<std::vector<int>> contrast_enhancement_par(std::vector<std::vector<int>> pic, double alpha, int beta) {
    int rows = pic.size();
    int cols = pic[0].size();
    int pic_size = rows * cols;
    int num_of_proc;
    int proc_num;
    MPI_Comm_size(MPI_COMM_WORLD, &num_of_proc);
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_num);
    int displs_size = num_of_proc + 1;
    int* num_of_pixels = new int[num_of_proc];
    int* displs = new int[displs_size];
    int rest = 0;
    int trest = 0;
    int i = 0;
    int sum = 0;
    std::vector<int> tmp(pic_size);
    std::vector<std::vector<int>> res(rows, std::vector<int>(cols));
    for (int x = 0; x < rows; x++) {
        for (int y = 0; y < cols; y++) {
            tmp[i] = pic[x][y];
            i++;
        }
    }
    if (pic_size == 0)
        throw "Error. Picture is empty!";
    if (num_of_proc > pic_size) {
        throw "Error. Number of processes is bigger then the picture size!";
    } else {
        for (int i = 0; i < num_of_proc; i++) {
            num_of_pixels[i] = pic_size / num_of_proc;
            rest = pic_size % num_of_proc;
            if (rest > 0) {
                num_of_pixels[i]++;
                rest--;
            }
            displs[i] = sum;
            sum += num_of_pixels[i];
        }
    }
    displs[num_of_proc] = pic_size;
    for (int i = 0; i < num_of_proc - 1; i++) {
        trest += num_of_pixels[i];
    }
    num_of_pixels[num_of_proc - 1] = pic_size - trest;
    std::vector<int> tmp_res(num_of_pixels[proc_num]);
    MPI_Scatterv(tmp.data(), num_of_pixels, displs, MPI_INT, tmp_res.data(),
        num_of_pixels[proc_num], MPI_INT, 0, MPI_COMM_WORLD);

    if (0 == proc_num) {
        for (int i = 0; i < num_of_pixels[proc_num]; i++) {
            tmp_res[i] = barrier(alpha * tmp[i] + beta);
        }
    } else {
        int t = 0;
        for (int i = displs[proc_num]; i < displs[proc_num + 1]; i++) {
            tmp_res[t] = barrier(alpha * tmp[i] + beta);
            t++;
        }
    }

    std::vector<int> _tmp(pic_size);
    i = 0;
    MPI_Gatherv(tmp_res.data(), num_of_pixels[proc_num], MPI_INT, _tmp.data(),
        num_of_pixels, displs, MPI_INT, 0, MPI_COMM_WORLD);
    for (int x = 0; x < rows; x++) {
        for (int y = 0; y < cols; y++) {
            res[x][y] = _tmp[i];
            i++;
        }
    }

    return res;
}
