//
// Created by Tea on 19-11-2.
//

#include "Calibrator.h"

cv::Mat Calibrator::camera_Matrix = cv::Mat();
cv::Mat Calibrator::dist_Coeffs = cv::Mat();

Calibrator::Calibrator(setter &set,MindVisionCamera &tempCamera)//传入的参数是setter中的地址和工业相机的驱动
{
    const char* image_folders= set.SAVE_IMAGE_PATH.c_str();
    cv::Size board_size=set.CornersMatrix;
    cv::Size square_size=set.Rectangle;
    auto_Start(image_folders,tempCamera);
    std::vector<cv::String>filename;
    cv::glob(image_folders, filename);
    cv::Size image_size_temp;
    std::cout << "begin to add points..." << std::endl;
    int success=addChessBoardCorners(filename, board_size, square_size, image_size_temp);
    save_calibrate_result(set.CalibrationResultPath);//cr
    for (int i = 0; i < success; i++) {
        saveImagePoints(set.CalibrationPointPath, image_points[i], object_points[i]);//ip
        number++;
    }
    std::cout << number << std::endl;
}


int Calibrator::addChessBoardCorners(

        std::vector<cv::String> file_list,
        const cv::Size board_size,
        const cv::Size square_size,
        cv::Size& image_size
)//四个参数分别为文件名，板子角点数量，小块大小（单位毫米），图片尺寸

{
    Debug4(file_list.size())
    int success = 0;
    std::vector<cv::Point2f> image_corners;//像素坐标系
    std::vector<cv::Point3f> object_corners;//世界坐标系
    cv::Size winSize(5, 5);//卷积的窗口大小
    cv::Size zeroSize(-1, -1);//没有大小的Size
    for (size_t i = 0; i < board_size.height; i++)
        for (size_t j = 0; j < board_size.width; j++)
            object_corners.emplace_back(cv::Point3f(float(square_size.width * j), float(square_size.height * i), 0.0f));
    //emplace_back和push_back的区别
    for (size_t i = 0; i < file_list.size(); i++)
    {
        cv::Mat srcImage = cv::imread(file_list[i]);
        cv::Mat grayImage;
        cv::cvtColor(srcImage, grayImage, cv::COLOR_BGR2GRAY);
        image_size = grayImage.size();
        if (0 == cv::findChessboardCorners(srcImage, board_size, image_corners))
        {
            std::cout << "can not find corners" << std::endl;
            continue;
        }
        else
        {
            success++;
            cv::findChessboardCorners(grayImage, board_size, image_corners);
            cv::cornerSubPix(grayImage, image_corners, cv::Size(5, 5), cv::Size(-1, -1), cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 50, 0.001));
        }
        addPoints(image_corners, object_corners);
        cv::Mat image = srcImage.clone();
        cv::namedWindow("before", cv::WINDOW_NORMAL);
        cv::drawChessboardCorners(image, board_size, image_corners, false);
        cv::imshow("before", image);
        double error = Calibrate(image_size);
        std::cout << "error result" << error << std::endl;
        cv::Mat dstImage = remap_correct(image);
        cv::namedWindow("remap image", cv::WINDOW_NORMAL);
        cv::imshow("remap image", dstImage);
        cv::waitKey(30);
    }
    return success;
}

void Calibrator::addPoints(
        std::vector<cv::Point2f>image_corners,
        std::vector<cv::Point3f>object_corners
)

{
    image_points.push_back(image_corners);
    object_points.push_back(object_corners);
}

double Calibrator::Calibrate(
        cv::Size image_size_temp
)
{
    double result = cv::calibrateCamera(object_points, image_points, image_size_temp,
                                        camera_Matrix, dist_Coeffs, rvects, tvects, 0);//rvects��ת������tvectsλ������
    //camera_Matrix 相机内参 dist_Coeffs 畸变系数
    return result;
}


cv::Mat Calibrator::remap_correct(
        const cv::Mat& a_image
)
{
    cv::Size image_size = a_image.size();
    cv::Mat mapx(image_size, CV_32FC1);
    cv::Mat mapy(image_size, CV_32FC1);
    cv::Mat dstImage;
    cv::Mat newCameraMatrix;
    cv::Mat RRR = cv::Mat::eye(3, 3, CV_32F);
    //获得畸变映射关系
    cv::initUndistortRectifyMap(camera_Matrix, dist_Coeffs, RRR, newCameraMatrix, image_size, CV_32FC1, mapx, mapy);
    //上面的函数用于计算无畸变和修正转换映射
    //矫正图像
    cv::remap(a_image, dstImage, mapx, mapy, cv::INTER_LINEAR);
    return dstImage;
}



void Calibrator::save_calibrate_result(
        std::string output_filename
)

{
    std::map<std::string, cv::Mat> calibrator_Matrix;
    calibrator_Matrix["camera_Matrix"] = camera_Matrix;
    calibrator_Matrix["dist_Coeffs"] = dist_Coeffs;
    cv::FileStorage fs(output_filename, cv::FileStorage::WRITE);//д���ļ�
    for (auto camera_para : calibrator_Matrix)
    {
        fs << camera_para.first << camera_para.second;
    }
    fs.release();
    std::cout << "save file output" << std::endl;
    std::cout << "camera_Matrix" << camera_Matrix << std::endl;
    std::cout << "dist_Coeffs" << dist_Coeffs << std::endl;
    std::cout << "----------------( * - * )" << std::endl;
}


void Calibrator::read_calibrate_result(
        std::string output_filename
)
{
    cv::FileStorage fs(output_filename, cv::FileStorage::READ);
    fs["camera_Matrix"] >> camera_Matrix;
    fs["dist_Coeffs"] >> dist_Coeffs;
    fs.release();
}

void Calibrator::saveImagePoints(
        std::string output_filename,
        const std::vector<cv::Point2f>imagePoints,
        const std::vector<cv::Point3f>objectPoints
)

{
    cv::FileStorage fs(output_filename, cv::FileStorage::WRITE);
    std::cout << "Save ImagePoints" << std::endl;
    fs << "image_points" << "[";
    for (auto pt : imagePoints) {
        fs << pt;
        //std::cout << pt << std::endl;
    }
    fs << "]";
    fs << "object_points" << "[";
    for (auto pt : objectPoints) {
        fs << pt;
        //std::cout << pt << std::endl;
    }
    fs << "]";
    fs.release();
}


/*void Calibrator::readImagePoints(
        std::string output_filename,
        std::vector<cv::Point2f>& imagePoints,
        std::vector<cv::Point3f>& objectPoints
)
{
    cv::FileStorage fs(output_filename, cv::FileStorage::READ);
    std::cout << "Read ImagePoints" << std::endl;
    for (auto tmp_pt : fs["image_points"])
    {
        static int i = 0;
        cv::Point2f pt((float)tmp_pt[0], (float)tmp_pt[1]);
        imagePoints.emplace_back(pt);
        std::cout << i++ << "=" << pt << std::endl;
    }
    for (auto tmp_pt : fs["object_points"]) {
        static int i = 0;
        cv::Point3f pt((float)tmp_pt[0], (float)tmp_pt[1], (float)tmp_pt[2]);
        objectPoints.emplace_back(pt);
        std::cout << i++ << "=" << std::endl;
    }
    fs.release();
}*/

void Calibrator::auto_Start(
        const char* image_folders,MindVisionCamera &tempCamera
) {
    std::ostringstream picName;//用于保存图片名
    int timeCount = 0, i = 0;//用于计数
    //MindVisionCamera industryCamera2;
    tempCamera.SetExposureTime(30);
    //tempCamera.SetResolution(cv::Size(800,600),cv::Size(0,0));
    while (1) {
        cv::Mat src;
        tempCamera>>src;
        //cv::flip(src,src,-1);
        timeCount++;
        if (50 == timeCount && i < 50) {
            //循环25次，每隔1.5秒自动拍一次照片，保存至规定文件夹
            timeCount = 0;
            i++;
            picName << image_folders << "/" << i << ".jpg" << std::endl;
            std::cout << picName.str() << std::endl;
            imwrite(picName.str(), src);
            std::cout << "one picture catched" << std::endl;
            picName.str("");//清空字符串
        }
        cv::imshow("pic", src);
        cv::waitKey(1);
        if (50 == i) {
            cv::destroyAllWindows();
            break;
        }
    }
}