import QtQuick 2.2
import QtQuick.Controls 2.2
import QMLBridge 1.0

ApplicationWindow {
    id: appWindow
    visible: true
    width: 800
    height: 600
    title: "Music Player"
    
    Component.onCompleted: {
        console.log("应用启动")
    }
    Component.onDestruction: {
        console.log("应用关闭")
    }

    QMLBridge {
        id: bridge 
        onProgressChanged: {
            console.log("播放进度调整为：", progress * 100, "%")
        }
        onVolumeChanged: {
            console.log("播放音量调整为：", volume * 100, "%")
        }
    }
    
    Rectangle {
        id: songInfoBar
        anchors.top: parent.top
        visible: false
        width: parent.width
        height: parent.height - bottomBar.height
        color: "transparent" // 设置透明背景
        
        Rectangle {
            anchors.left: parent.left
            width: parent.width * 0.4
            height: parent.height
            color: "transparent"

            Image {
                id: singCover
                anchors.top: parent.top
                width: parent.width
                height: parent.width    
                source: bridge.imgPath
                fillMode: Image.PreserveAspectFit                   
                anchors.horizontalCenter: parent.horizontalCenter
            }
            
            Text {
                id: singName
                anchors.top: singCover.bottom
                text: "歌名：" + bridge.songName
                font.pixelSize: 16
                anchors.horizontalCenter: parent.horizontalCenter
            }  
            
            Text {
                id: singerName
                anchors.top: singName.bottom
                text: "歌手：" + bridge.artist
                font.pixelSize: 16
                anchors.horizontalCenter: parent.horizontalCenter
            }
            
            Text {
                anchors.top: singerName.bottom
                text: "时长：" + bridge.duration
                font.pixelSize: 16
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }

        Rectangle {
            anchors.right: parent.right
            width: parent.width * 0.45
            height: parent.height
            color: "transparent"
            
            ListView {   
                anchors.bottom: parent.bottom
                width: parent.width
                height: parent.height * 0.8
                spacing: 10
                model: bridge.lyrics
                delegate: Text {
                    text: modelData
                    font.pixelSize: 16
                    horizontalAlignment: Text.AlignHCenter
                }
            }
        }
    }

    Rectangle {
        id: bottomBar
        anchors.bottom: parent.bottom
        width: parent.width
        height: 50
        color: "lightgray"

        Row {
            anchors.centerIn: parent
            spacing: 10
            
            Rectangle {
                width: 40
                height: 40
                Image {
                    anchors.fill: parent
                    source: bridge.imgPath
                    fillMode: Image.PreserveAspectCrop
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }

            Button {
                text: "上一首"
                onClicked: {
                    console.log("切换到上一首")
                }
            }

            Button {
                text: bridge.isPlaying ? "暂停" : "播放"
                onClicked: {
                    bridge.isPlaying = !bridge.isPlaying
                    console.log(bridge.isPlaying ? "点击播放" : "点击暂停")
                }
            }

            Button {
                text: "下一首"
                onClicked: {
                    console.log("切换到下一首")
                }
            }

            Slider {
                width: 200
                value: bridge.progress
                onValueChanged: {
                    bridge.progress = value.toFixed(2)
                    // 此处日志输出在QMLBridge的progressChanged信号之后
                }
            }
            
            Button {
                text: "音量"
                onClicked: {
                    volumePopup.open()
                }
                Popup {
                    id: volumePopup
                    width: 20
                    height: 100
                    y: -100
                    Slider {
                        width: parent.width
                        height: parent.height
                        z: 1
                        orientation: Qt.Vertical
                        value: bridge.volume
                        onValueChanged: {
                            bridge.volume = value.toFixed(2)
                            // 此处日志输出在QMLBridge的volumeChanged信号之后
                        }
                    }
                }
            }

            Button {  
                text: "歌曲信息"
                onClicked: {
                    if (songInfoBar.visible) {
                        songInfoBar.visible = false
                        console.log("隐藏歌曲信息")
                    } else {
                        songInfoBar.visible = true
                        console.log("显示歌曲信息")   
                    }
                }
            }
        
        }
    }

}