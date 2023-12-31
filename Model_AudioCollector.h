#pragma once
#include <qobject.h>
#include <QQueue>
#include "MyStruct.h"
#include "DataPack.h"
#include <QMutex>
#include <QTimer>
#include <QThread>

//class DataPack;
class View_TabWidget_Setting;

using namespace MYSTRUCT;




class Model_AudioCollector :public QObject
{
	Q_OBJECT
public:
	explicit Model_AudioCollector(View_TabWidget_Setting *handle,QObject* parent = nullptr);
	Model_AudioCollector();
	~Model_AudioCollector();
	void setView(View_TabWidget_Setting* handle);
	void start();
	void stop();

protected:
	void init();
private:
	void initConnect();
	void initMember();
	void read();

signals:
	void on_signal_stopTimer();
	void on_signal_startTimer();
public:
	//存储原始数据
	QQueue<RawDataPack> mRawData;
	//数据包
	RawDataPack mRawDataPack;
	//数据锁
	QMutex mMutex;
	//采集卡类型
	int mCaptrueType = CAPTURETYPE::SoundCard;
	//自启动线程
	QThread mThread;
protected:
	//通道数据
	double p[4800], x[4800], y[4800], z[4800];
	//控制读取间隔
	QTimer mTimer;

private:
	//获取NI对象或声卡对象
	View_TabWidget_Setting* mView_TabWidget_Setting = nullptr;
};

