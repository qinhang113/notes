#include "pch.h"
#include "ImgPara4.h"

bool ImgPara4::LoadFromFile(char* path)
{
    std::ifstream is(path);
    if (is.is_open())
    {
        templateSortIndex.clear();
        templateAreas.clear();
        int value;
        is >> value;
        for (int i = 0; i < value; i++)
        {
            int index;
            is >> index;
            templateSortIndex.push_back(index);
        }
        for (int i = 0; i < value; i++)
        {
            float area;
            is >> area;
            templateAreas.push_back(area);
        }
        is.close();
        return true;
    }
    return false;
}

bool ImgPara4::SaveToFile(char* path)
{
    std::ofstream os(path);
    os << templateSortIndex.size()<< "\n";
    for (auto& index : templateSortIndex)
    {
        os << index << " ";
    }
    os << "\n";

    for (auto& area : templateAreas)
    {
        os << area << " ";
    }
    os.close();
    return true;
}
/**************
* 1.��ͬ�Ŀ�������ܹ��յ�ԭ��Ҷ�ֵ��С�ı仯(0xA5 - 0xDC)�����и�˹�˲�������Ӱ�졣�����ܻ���жϲ���ȷ
* 2.ʹ����ֵ0xA0����2ֵ��(<0xA0����Ϊ��ɫ������0xA0��Ϊ��ɫ)��Ȼ��ȡ�����������ж�������Ⱦ
* 3.ʹ����ֵ0xDD����2ֵ����Ȼ��ȡ�����������ж����޻���
**************/
bool ImgPara4::ImgProcessing(cv::Mat& src, cv::Mat& dst)
{
    dst.release();
    src.copyTo(dst);
    CString strShow;
    if (templateSortIndex.size() == 0)
    {
        strShow = _T("δ����ģ��!\n");
        TRACE(strShow);
        return false;
    }

    cv::Mat grayImg, img_edge;
    cv::cvtColor(src, grayImg, cv::COLOR_BGR2GRAY);

    //cv::GaussianBlur(grayImg, grayImg, cv::Size(3, 3), 3);
    cv::threshold(grayImg, img_edge, 0xA0, 255, cv::THRESH_BINARY);
    std::vector< std::vector< cv::Point > > contours;
    std::vector< cv::Vec4i > hierarchy;

    cv::findContours(
        img_edge,
        contours,
        hierarchy,
        cv::RETR_LIST,
        cv::CHAIN_APPROX_SIMPLE
    );

    std::vector<int> sortIdx(contours.size());
    std::vector<float> areas(contours.size());
    for (int n = 0; n < (int)contours.size(); n++) {
        sortIdx[n] = n;
        areas[n] = contourArea(contours[n], false);
    }
    //���������������
    std::sort(sortIdx.begin(), sortIdx.end(), AreaCmp(areas));
    if (contours.size() < templateSortIndex.size())
    {
        strShow = _T("����Ⱦ!\n");
        TRACE(strShow);
        return false;
    }
    bool re = true;
    //������������ģ��
    if (contours.size() > templateSortIndex.size())
    {
        for (int i = templateSortIndex.size(); i < contours.size(); i++)
        {
            int index = sortIdx[i];
            if (areas[index] > 5)
            {
                cv::drawContours(
                    dst, contours, index,
                    //BGR��ɫ
                    cv::Scalar(255, 0, 255), 1, 8, hierarchy,
                    0
                );
                strShow.Format(_T("����Ⱦ(%d�������:%.2lf)!\n"), i, areas[index]);
                TRACE(strShow);
                re = false;
            }
        }
    }
    for (int i = 0; i < templateSortIndex.size(); i++)
    {
        int index1 = templateSortIndex[i];
        int index2 = sortIdx[i];
        float a1 = templateAreas[index1];
        float a2 = areas[index2];
        if (!CompareArea(a1, a2))
        {
            cv::drawContours(
                dst, contours, index2,
                //BGR��ɫ
                cv::Scalar(0, 0, 255), 1, 8, hierarchy,
                0
            );
            CString str;
            str.Format(_T("��%d��������ģ�岻ƥ��(%.2lf,%.2lf)!\n"), i, a1, a2);
            TRACE(str);
            re = false;
        }
        else
        {
            cv::drawContours(
                dst, contours, index2,
                //BGR��ɫ
                cv::Scalar(0, 255, 0), 1, 8, hierarchy,
                0
            );
        }
    }
    bool r = JudgeScratch(grayImg, dst);
    re = re && r;
    return re;
}

bool ImgPara4::SetTemplateImg(cv::Mat& src, cv::Mat& dst)
{
    templateSortIndex.clear();
    templateAreas.clear();

    dst.release();
    src.copyTo(dst);
    cv::Mat grayImg, img_edge;
    cv::cvtColor(src, grayImg, cv::COLOR_BGR2GRAY);
    //cv::GaussianBlur(grayImg, grayImg, cv::Size(3, 3), 3);
    cv::threshold(grayImg, img_edge, 0xA0, 255, cv::THRESH_BINARY);
    std::vector< std::vector< cv::Point > > contours;
    std::vector< cv::Vec4i > hierarchy;

    cv::findContours(
        img_edge,
        contours,
        hierarchy,
        cv::RETR_LIST,
        cv::CHAIN_APPROX_SIMPLE
    );
    if (contours.size() > 20 || contours.size() < 5)
    {
        TRACE("ģ�岻�Ϲ淶!\n");
        return false;
    }

    int index = 0;
    for (int n = 0; n < (int)contours.size(); n++) {
        double area = contourArea(contours[n], false);
        if (area < 10)
        {
            continue;
        }
        templateSortIndex.push_back(index);
        templateAreas.push_back(area);
        cv::drawContours(
            dst, contours, n,
            //BGR��ɫ
            cv::Scalar(0, 255, 0), 1, 8, hierarchy,
            0
        );
        index++;
    }
    // sort contours so that the largest contours go first
    //
    std::sort(templateSortIndex.begin(), templateSortIndex.end(), AreaCmp(templateAreas));
    return true;
}

bool ImgPara4::CompareArea(double a1, double a2)
{
    return !(abs(a1 - a2) / std::max(a1,a2) > 0.02);
}

bool ImgPara4::JudgeScratch(cv::Mat& src, cv::Mat& dst)
{
    cv::Mat img_edge;
    cv::threshold(src, img_edge, 0xDD, 255, cv::THRESH_BINARY);
    std::vector< std::vector< cv::Point > > contours;
    std::vector< cv::Vec4i > hierarchy;

    cv::findContours(
        img_edge,
        contours,
        hierarchy,
        cv::RETR_LIST,
        cv::CHAIN_APPROX_SIMPLE
    );

    std::vector<int> sortIdx(contours.size());
    std::vector<float> areas(contours.size());
    for (int n = 0; n < (int)contours.size(); n++) {
        sortIdx[n] = n;
        areas[n] = contourArea(contours[n], false);
    }
    //���������������
    std::sort(sortIdx.begin(), sortIdx.end(), AreaCmp(areas));

    bool re = true;
    for (int i = 0; i < sortIdx.size(); i++)
    {
        int index = sortIdx[i];
        float a = areas[index];
        if (a > 10)
        {
            cv::drawContours(
                dst, contours, index,
                //BGR��ɫ
                cv::Scalar(255, 0, 0), 1, 8, hierarchy,
                0
            );
            re = false;
        }
        else
        {
            break;
        }
    }
    return re;
}
