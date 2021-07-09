#ifndef tocabi_gui__TocabiGUI_H
#define tocabi_gui__TocabiGUI_H

#include <rqt_gui_cpp/plugin.h>
#include <tocabi_gui/ui_tocabi_gui.h>

#include <sensor_msgs/Imu.h>
#include <sensor_msgs/JointState.h>
#include <ros/macros.h>

#include <QList>
#include <QString>
#include <QSize>
#include <QWidget>
#include <QObject>
#include <QStateMachine>
#include <QState>
#include <QEventTransition>
#include <ros/ros.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Float32MultiArray.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Int32MultiArray.h>
#include <std_msgs/Int8.h>
#include <std_msgs/Int8MultiArray.h>
#include <geometry_msgs/PolygonStamped.h>
#include <std_msgs/String.h>
#include <QMetaType>

#include <QGraphicsRectItem>
#include <QGraphicsSceneWheelEvent>
#include <QStringListModel>
#include <QSignalMapper>

#include "tocabi_msgs/TaskCommand.h"
#include "tocabi_msgs/TaskCommandQue.h"
#include "tocabi_msgs/TaskGainCommand.h"
#include "tocabi_msgs/VelocityCommand.h"
#include "tocabi_msgs/positionCommand.h"

const double NM2CNT[33] =
    {       //Elmo 순서
        95, //head
        95,
        95, //wrist
        95,
        95,
        95,
        15.5, //shoulder3
        15.5, //arm
        15.5, //arm
        15.5, //shoulder3
        42,   //Elbow
        42,   //Forearm
        42,   //Forearm
        42,   //Elbow
        15.5, //shoulder1
        15.5, //shoulder2
        15.5, //shoulder2
        15.5, //shoulder1
        3.3,  //Waist
        3.3,
        5.8, //rightLeg
        4.3,
        3.8,
        3.46,
        3.52,
        12.33,
        3.3, //upperbody
        5.8, //leftLeg
        4.3,
        3.8,
        3.46,
        3.52,
        12.33};

//leftleg rightleg waist leftarm head rightarm

const double posStandard[33] = {0.0, 0.0, -0.24, 0.6, -0.36, 0.0,
                                0.0, 0.0, -0.24, 0.6, -0.36, 0.0,
                                0, 0, 0,
                                0.3, 0.3, 1.5, -1.27, -1, 0, -1, 0,
                                0, 0,
                                -0.3, -0.3, -1.5, 1.27, 1, 0, 1, 0};
const double posStandard2[33] = {0.0, 0.0, -0.93, 1.24, -0.5, 0.0,
                                 0.0, 0.0, -0.93, 1.24, -0.5, 0.0,
                                 0, 0.44, 0,
                                 -0.39, -1.205, 1, -0.375, -1.1, 2.31, -1.176, 0.15,
                                 0, 0,
                                 0.39, 1.205, -1, 0.375, 1.1, -2.31, 1.176, -0.15};
const double posStandard3[33] = {0.01920543546875, 0.014871940644527501, -0.9358508043751563, 1.338121842500375, -0.5674653948051875, 0.050828442832027504,
                                 0.0705680103, -0.06239465556640125, -0.8990736226364687, 1.1964587462107499, -0.4385266665035625, 0.0016720387109400003,
                                 0.00085875627915, 0.4494140928808593, 0.04510635186519375,
                                 -0.5609804923725624, -1.1437550122563438, 0.9443183765642187, -0.34260309411968737, -1.0029662848342813, 2.2997703634082023, -1.0719877360214063, 0.1035897010547,
                                 0.0015608251269812537, 0.014461600869112495,
                                 0.5184163693160313, 1.1251018097560312, -0.931678377501875, 0.36133671315124993, 1.0657751151269375, -2.643443347626953, 1.121776907089875, 0.23148915758789498};

const double posStandard4[33] = {-0.0024006794335925006, -0.0163752415038875, -0.2397534773632875, 0.5841320925976938, -0.37639278761696876, 0.013966892167993749, -0.013956522459999999, -0.05586756867183125, -0.24702454478515623, 0.604725780390375, -0.36744968148409374, 0.06033145183595626, 0.00328563609915, -0.0002761164843624996, -0.005580197773481246, 0.7394552849604688, -0.06400917000946874, 1.3822352858254687, -2.512951525376063, -2.2867085197168064, -0.15787726984375625, 0.9463700754394188, -0.10044504109376251, -0.039350433974599995, 0.07545266430668125, -0.2857076972558437, -0.28594929917966877, -1.4355986313832814, 1.2741931502969999, 0.9974094405859125, -0.0015378154198750216, 0.9348268724121, -0.07143747042969376};

struct task_que
{
    std::string task_title;
    tocabi_msgs::TaskCommand tc_;
};

namespace tocabi_gui
{

    class MyQGraphicsScene : public QGraphicsScene
    {
        Q_OBJECT
    public:
        explicit MyQGraphicsScene(QWidget *parent = 0);
        virtual void wheelEvent(QGraphicsSceneWheelEvent *event);
        //virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);

    public slots:

    private:
    };

    class MyQGraphicsView : public QGraphicsView
    {
        Q_OBJECT
    public:
        explicit MyQGraphicsView(QWidget *parent = 0);
        //virtual void wheelEvent(QGraphicsViewWheelEvent *event);
        //virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);

    public slots:

    private:
    };

    class TocabiGui : public rqt_gui_cpp::Plugin
    {
        Q_OBJECT
    public:
        TocabiGui();

        virtual void initPlugin(qt_gui_cpp::PluginContext &context);
        virtual void shutdownPlugin();
        virtual void saveSettings(qt_gui_cpp::Settings &plugin_settings, qt_gui_cpp::Settings &instance_settings) const;
        virtual void restoreSettings(const qt_gui_cpp::Settings &plugin_settings, const qt_gui_cpp::Settings &instance_settings);

    protected slots:
        virtual void plainTextEditcb(const std_msgs::StringConstPtr &msg);
        virtual void ecatpbtn();
        virtual void statpbtn();
        virtual void commandpbtn();
        virtual void safetyresetbtncb();
        virtual void mtunebtn();
        virtual void walkinginitbtncb();
        virtual void walkingstartbtncb();
        virtual void walkingbtn();
        virtual void avatarbtn();
        virtual void sendtunebtn();
        virtual void resettunebtn();
        virtual void pointcb(const geometry_msgs::PolygonStampedConstPtr &msg);
        virtual void imucb(const sensor_msgs::ImuConstPtr &msg);
        virtual void timercb(const std_msgs::Float32ConstPtr &msg);
        virtual void tasksendcb();
        virtual void customtaskgaincb(int state);
        virtual void safety2btncb();
        virtual void que_downbtn();
        virtual void que_upbtn();
        virtual void que_deletebtn();
        virtual void que_resetbtn();
        virtual void que_sendbtn();
        virtual void que_addquebtn();

        virtual void gs_test();



        //virtual void turnon_robot();
        virtual void sysstatecb(const std_msgs::Int8MultiArrayConstPtr &msg);
        virtual void ecatstatecb(const std_msgs::Int8MultiArrayConstPtr &msg);
        virtual void solvermode_cb(int state);
        virtual void sendtaskgaincommand();
        virtual void resettaskgaincommand();
        virtual void slidervelcommand();
        virtual void sliderrel1();
        virtual void sliderrel2();
        virtual void sliderrel3();
        virtual void positionCommand();
        virtual void positionPreset1();
        virtual void positionPreset2();
        virtual void positionPreset3();
        virtual void positionPreset4();
        virtual void positionRelative(int index);

        virtual void taskmodecb(int index);

        virtual void sendCommand(QString str);

        //dg
        // virtual void walkingspeedcb(int value);
        // virtual void walkingdurationcb(int value);
        // virtual void walkingangvelcb(int value);
        // virtual void kneetargetanglecb(int value);
        // virtual void footheightcb(int value);
        
        virtual void sendupperbodymodecb();

        virtual void sendstillposecalibration();
        virtual void sendtposecalibration();
        virtual void sendforwardposecalibration();
        virtual void sendresetposecalibration();
        virtual void sendloadsavedcalibration();

        virtual void vr_eye_depth_cb(int value);
        virtual void vr_eye_distance_cb(int value);

        virtual void torqueCommand();
        void handletaskmsg();

    private:
        //ROS_DEPRECATED virtual QList<QString>
        std::vector<task_que> tq_;

        Ui::TocabiGuiWidget ui_;
        QWidget *widget_;

        //QStringListModel *model;
        //QStringList list;

        std::vector<QLabel *> ecatlabels;
        std::vector<QLabel *> safetylabels;
        std::vector<QLabel *> zplabels;
        std::vector<QLineEdit *> ecattexts;
        MyQGraphicsScene *scene;
        MyQGraphicsView *view;

        QGraphicsEllipseItem *com_d;
        QGraphicsRectItem *rfoot_d;
        QGraphicsLineItem *rfoot_l1;
        QGraphicsLineItem *rfoot_l2;
        QGraphicsRectItem *lfoot_d;
        QGraphicsLineItem *lfoot_l1;
        QGraphicsLineItem *lfoot_l2;
        QGraphicsRectItem *Pelv;
        QGraphicsEllipseItem *zmp;

        QGraphicsEllipseItem *rfoot_c;
        QGraphicsEllipseItem *lfoot_c;
        QGraphicsEllipseItem *rhand_c;
        QGraphicsEllipseItem *lhand_c;

        double robot_time;

        ros::NodeHandle nh_;

    public:
        ros::Subscriber timesub;
        ros::Subscriber jointsub;
        ros::Subscriber pointsub;
        ros::Subscriber guilogsub;
        ros::Publisher gain_pub;
        std_msgs::Float32MultiArray gain_msg;
        ros::Publisher com_pub;
        std_msgs::String com_msg;

        ros::Subscriber ecat_sub;


        ros::Publisher poscom_pub;
        tocabi_msgs::positionCommand poscom_msg;

        ros::Publisher task_pub;
        tocabi_msgs::TaskCommand task_msg;

        ros::Publisher task_que_pub;
        tocabi_msgs::TaskCommandQue task_que_msg;

        ros::Publisher taskgain_pub;
        tocabi_msgs::TaskGainCommand taskgain_msg;

        ros::Publisher velcommand_pub;
        tocabi_msgs::VelocityCommand velcmd_msg;

        //dg
        // ros::Publisher walkingspeed_pub;
        // std_msgs::Float32 walkingspeed_msg;
        // ros::Publisher walkingduration_pub;
        // std_msgs::Float32 walkingduration_msg;
        // ros::Publisher walkingangvel_pub;
        // std_msgs::Float32 walkingangvel_msg;
        // ros::Publisher kneetargetangle_pub;
        // std_msgs::Float32 kneetargetangle_msg;
        // ros::Publisher footheight_pub;
        // std_msgs::Float32 footheight_msg;

        //avatar
        ros::Publisher upperbodymode_pub;
        std_msgs::Int8 upperbodymode_msg;
        ros::Publisher pose_calibration_pub;
        std_msgs::Int8 pose_calibration_msg;
        ros::Publisher vr_slider_pub;
        std_msgs::Float32MultiArray vr_slider_msg;

        ros::Subscriber sysstatesub;

        ros::Subscriber imusub;

        //void guiLogCallback(const std_msgs::StringConstPtr &msg);
        std::string logtext;

        double com_height = 0;
        double pelv_pitch = 0;
        double upper_pitch = 0;

    signals:
        void guiLogCallback(const std_msgs::StringConstPtr &msg);
        void pointCallback(const geometry_msgs::PolygonStampedConstPtr &msg);
        void timerCallback(const std_msgs::Float32ConstPtr &msg);
        void imuCallback(const sensor_msgs::ImuConstPtr &msg);
        void sysstateCallback(const std_msgs::Int8MultiArrayConstPtr &msg);
        void ecatstateCallback(const std_msgs::Int8MultiArrayConstPtr &msg);
        void guiLogSignal();
    };

} // namespace tocabi_gui
Q_DECLARE_METATYPE(std_msgs::StringConstPtr);
Q_DECLARE_METATYPE(geometry_msgs::PolygonStampedConstPtr);
Q_DECLARE_METATYPE(std_msgs::Float32ConstPtr);
Q_DECLARE_METATYPE(sensor_msgs::ImuConstPtr);
Q_DECLARE_METATYPE(std_msgs::Int32MultiArrayConstPtr);
Q_DECLARE_METATYPE(std_msgs::Int8MultiArrayConstPtr);

#endif
