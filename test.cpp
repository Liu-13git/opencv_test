#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
    Mat src = imread("test.jpg");
    if (src.empty())
    {
        cout << "图片读取失败！检查图片路径！" << endl;
        return -1;
    }
    cout << "图像宽：" << src.cols << " , 图像高：" << src.rows << endl;

    //基础：转灰度图
    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    imwrite("01_gray.jpg", gray);

    //基础：二值化
    Mat binary;
    threshold(gray, binary, 127, 255, THRESH_BINARY);
    imwrite("02_binary.jpg", binary);

    //基础：统计非零像素
    int non_zero_gray = countNonZero(gray);
    int non_zero_binary = countNonZero(binary);
    cout << "灰度图非零像素数量：" << non_zero_gray << endl;
    cout << "二值图非零像素数量：" << non_zero_binary << endl;


    //ROI裁剪
    Rect roi(60, 60, 220, 220);  // x起始,y起始,宽度,高度
    Mat roi_img = src(roi);
    imwrite("03_roi_cut.jpg", roi_img);
    cout << "ROI裁剪图已保存" << endl;

    //图像缩放
    Mat resize_img;
    resize(src, resize_img, Size(), 0.5, 0.5); // 宽高缩至原来0.5倍
    imwrite("04_resize.jpg", resize_img);
    cout << "缩放图像已保存" << endl;

    //HSV颜色筛选
    Mat hsv, mask_green;
    cvtColor(src, hsv, COLOR_BGR2HSV);
    //HSV绿色阈值
    Scalar lower_green(35, 40, 40);
    Scalar upper_green(77, 255, 255);
    inRange(hsv, lower_green, upper_green, mask_green);
    imwrite("05_hsv_mask.jpg", mask_green);
    cout << "HSV颜色筛选图已保存" << endl;

    //高斯模糊 + 二值化对比
    Mat blur_img;
    GaussianBlur(gray, blur_img, Size(5, 5), 0);
    Mat binary_blur;
    threshold(blur_img, binary_blur, 127, 255, THRESH_BINARY);
    imwrite("06_blur_binary.jpg", binary_blur);
    cout << "高斯模糊后二值图已保存，用于对比" << endl;

    //Canny边缘检测
    Mat edge;
    Canny(gray, edge, 50, 150);
    imwrite("07_canny_edge.jpg", edge);
    cout << "Canny边缘检测图已保存" << endl;


    cout << "01_gray.jpg      灰度图" << endl;
    cout << "02_binary.jpg    原图直接二值图" << endl;
    cout << "03_roi_cut.jpg   ROI裁剪" << endl;
    cout << "04_resize.jpg    缩放后图像" << endl;
    cout << "05_hsv_mask.jpg  HSV颜色掩码" << endl;
    cout << "06_blur_binary.jpg 高斯模糊后二值图" << endl;
    cout << "07_canny_edge.jpg  Canny边缘图" << endl;

    return 0;
}