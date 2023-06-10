#pragma once
#include <qobject.h>
#include <QThread>
#include <QTimer>
#include <QMutex>
#include <QMutexLocker>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include "GlobalConfig.hpp"



class View_hotMapAndVideoDisplay;
class Model_AudioCollector;
class Model_VideoDevice;
class CustomHm;
/**
 * ���ܣ�
 * 1������P1_D��648000�����ݽ��в�ֵ
 * 2����ֵ�������ʾ��Ⱦ
 */

class Model_hotMapAndVideoDisplay :public QObject
{
	Q_OBJECT
public:
	Model_hotMapAndVideoDisplay(View_hotMapAndVideoDisplay* handle = nullptr, Model_VideoDevice* _handle = nullptr);
	~Model_hotMapAndVideoDisplay();
	void setView(View_hotMapAndVideoDisplay* handle);
	void start();//��ʼ��Ⱦ
	void stop();//ֹͣ��Ⱦ
	void On_setHmFactorValue(unsigned short value);
	void on_setHmThreshold(double value);
	void on_setP1_DValue(double value);
protected:
	void initMember();
	void initConnect();
private:
	void init();
	void invokeDll();
	void renderHM(const double*);//��Ⱦ����ͼ
	void renderFM();//��Ⱦ��Ƶ֡
	void on_setXAxisCutoutValue(unsigned short);
	void on_setYAxisCutoutValue(unsigned short);
signals:
	void on_signal_replot_video();
	void on_signal_replot_hotmap();
	void on_signal_setMaxValue(QPoint p);
public:
	QMutex mMutex;
	//δ��ֵ������ͼ����
	double* _pP1_DData = nullptr;
	//P_1D_MAX_lvsĿǰ���ֵ
	double P_1D_MAX_lvs;
protected:
	QThread _mThread;
	QTimer* _pTimer = nullptr;
	//�ü���Χ
	quint16 mXAxisCutOut = 30, mYAxisCutOut = 30;
	//��ɫ��ֵ
	double posColor[5] = { 0.93,0.95,0.98,0.99,1 };
	//����ͼ��Сϵ��
	double mHmSizeFactor = 0.0f;
	//����ͼ�Ƿ���ʾϵ��������Ϊ1
	float hotMapCoefficient = 1;
	//��ʾ��ֵ
	double hotMapCoefficientvalue = 0;
	//��ɫ��ֵ
	//double posColor[5] = { 0.93,0.95,0.98,0.99,1 };
private:
	View_hotMapAndVideoDisplay* _pView_hotMapAndVideoDisplay = nullptr;

	//��ֵ����
	int interp_multiple = 2;
	// ��ֵ�������ͼ����
	//double* Fine_S = new double[2332800];//6����ֵ
	double* Fine_S = new double[259200];//2����ֵ
	//testdlldata
	double* FINE_S = new double[10800];

	//��Ƶ�ӿ�
	Model_VideoDevice *mModel_VideoDevice = nullptr;

	//����ͼ��Ⱦ QPainter+QImage�汾
	CustomHm *_pCustomHm = nullptr;

	//���س���
	int mPixWidth = PIXWIDTH;
	int mPixHight = PIXHIGHT;
	//ӳ���
	int mWidthPixRate;
	int mHightPixRate;
	//���ֵλ��
	QPoint mMaxPoint;
	//Դͼ
	//QImage mImage;
	//��ͼ�������еĵ�
	MyPoint mPoint;
	//��ͼ�İ뾶
	int mRadius = 50;
	//�ü�ֵ�е����ֵ
	double mCutoutMax = 0.0f;
	//���ֵλ�ڲü������е�λ��
	QPoint mMaxPos;

	//�ü�ƫ��
	int mOffset = 45;
};
