#include "dashboard.h"

DashBoard::DashBoard(QString e_id)
{

    db = QSqlDatabase::database("xitong");
    query = new QSqlQuery(db);
    if(!db.open())
    {
        QMessageBox::critical(0, QObject::tr("打开数据库失败！"), db.lastError().text());
    }
      initform(e_id);
}

void DashBoard::initform(QString e_id){
    query->prepare(QString("SELECT COUNT(*) AS nums FROM e_qml WHERE e_id = '%1' ").arg(e_id));
        if (!query->exec()) {
            qWarning() << "Error: unable to select nums";
            empty_sensor.setText("暂无传感器数据");
            empty_sensor.setAlignment(Qt::AlignCenter);
            empty_sensor.show();

        }
        // 读取查询结果
        int nums = 0;
        if (query->next()) {
            nums = query->value("nums").toInt(); // 获取nums列的值并转换为整数
        }
        qDebug() << "当前共有" << nums << "个数值";
        query->finish();
        QGridLayout *dash_show = new QGridLayout(this);
        int row=0, col=0;//遍历webview

        query->prepare(QString("SELECT qml_address,sensor_type FROM e_qml WHERE e_id = '%1' ").arg(e_id));
            if (!query->exec()) {
                qWarning() << "Error: unable to select qml";
            }
            while(query->next()){
                QWebEngineView *webView = new QWebEngineView;
                webView->page()->setBackgroundColor(Qt::transparent);
                webViews << webView;
                dash_show->addWidget(webView,row,col);
                QUrl url("E:/qt/project/xitongnew/echarts_test/gauge.html");
                webView->load(url);

                QWebSocket *web = new QWebSocket();
                web->open(query->value(0).toString());

                connect(web, &QWebSocket::connected, [=]() {
                    qDebug() << "连接websocket成功" ;
                });

                connect(web, &QWebSocket::disconnected, [=]() {
                    qDebug() << "断开websocket连接" ;
                });

                connect(web, &QWebSocket::textMessageReceived, [=](const QString &message) {
                    qDebug() << "接收信息： " << message;
                    message_recieve=message.toFloat();
                });
                sensor_type = query->value(1).toString();
                qDebug() << "当前传感器类型为：" << sensor_type;
                qDebug() << "传递的为：" << getunit(sensor_type) << "应该为：" <<message_recieve;
                //QString js = QString("setGaugeValue( %1,%2,%3);").arg(sensor_type).arg(message_recieve).arg(getunit(sensor_type));
                QString js = QString("setGaugeValue(%1)").arg(message_recieve);
                webView->page()->runJavaScript(js);


                 if(col>=2){
                     col=0;
                     row++;
                     continue;
                 }
                 col++;
            }

    }
QString DashBoard::getunit(QString type){
    // 对应传感器类型与单位
    QMap<QString, QString> unitMap;
        unitMap["温度"] = "℃";
        unitMap["油位"] = "";
        unitMap["倾角"] = "°";
        unitMap["加速度"] = "2";
        unitMap["CO浓度"] = "3";
        unitMap["CO2浓度"] = "4";
        unitMap["CH4浓度"] = "5";
        unitMap["粉尘浓度"] = "6";



        if (unitMap.contains(type)) {
            qDebug() << "应返回的单位：" << unitMap.value(type);
            return unitMap.value(type);
        } else {
            // 如果传感器类型未知，返回空字符串或其他默认值
            return "";
        }
    }



