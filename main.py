from re import L
from time import altzone
from maix import touchscreen, app, time, display, image,camera, nn
from maix._maix.image import COLOR_BLUE, COLOR_GREEN, COLOR_ORANGE, COLOR_PURPLE, COLOR_RED, COLOR_WHITE, COLOR_YELLOW, ApriltagFamilies
from maix._maix.time import time_diff, time_ms
from maix.v1.machine import UART
from maix import app, pinmap
from maix import uart

#导入模型
detector = nn.YOLOv5(model="best.mud", dual_buff=True)
GROUND_CENERY_X=-102    #地面场景下的坐标偏移量
GROUND_CENERY_Y=-65         
PAN_CENERY_X=-126       #平移场景下的坐标偏移量
PAN_CENERY_Y=-79
MAX_PAN=110             #平移和地面场景下物体尺寸的最大限制
MAX_GROUND=150
red_thresholds=[[0, 80, 0, 80, 10, 80]]        #红色阈值
green_thresholds=[[5,81,-57,-20,0,42]]         #绿色阈值5，81，-57，-20，0，42]
blue_thresholeds=[[0,70,-10,120,-128,-5]]      #蓝色阈值#测试0，58，-10，25，-55，-10

device = "/dev/ttyS0"
ser = uart.UART(device, 115200)
#device1 = "/dev/ttyS1"
#ser = UART("/dev/ttyS0", 115200)      #初始化串口
ts = touchscreen.TouchScreen()      #初始化触摸屏
disp = display.Display()            #初始化显示对象
camerahigh = 160        #定义摄像头图像的高度
camerawide = 140        #定义摄像头图像的宽度
windowcentre_x=int(camerahigh/2)        #屏幕中心点x（80）
windowcentre_y=int(camerawide/2)        #屏幕中心点y（70）
cam = camera.Camera(camerahigh, camerawide)     #初始化摄像头
img = cam.read()        #从摄像头读取一帧图像

#将字符转换为对应的 ASCII 码值，作为不同颜色和圆环识别结果的包头，用于串口通信
red_byte = ord('R')             #红色物块包头
green_byte = ord('G')           #绿色物块包头
blue_byte = ord('B')            #蓝色物块包头
red_circle_byte = ord('r')      #红色圆环包头
green_cirecle_byte = ord('g')   #绿色圆环包头
blue_circle_byte = ord('b')     #蓝色圆环包头

#用于在一组blob（图像中的连通区域）中找到面积最大的blob
def find_max(findblob_max):
    # 初始化 max_size 为 0 或其他合适的初始值
    max_size = 0    
    rect_max = 0     # 这个变量似乎没有被使用，如果需要可以保留
    max_blob = None  # 初始化 max_blob 为 None，表示还没有找到最大的 blob

    for m in findblob_max:
        # 计算当前 blob 的面积
        current_size = m[2] * m[3]
        # 如果当前 blob 的面积大于 max_size，则更新 max_size 和 max_blob
        if current_size > max_size:
            max_size = current_size
            max_blob = m

    # 返回找到的最大 blob
    return max_blob

#用于在地面场景下识别红、绿、蓝三种颜色的物体
def FIND_THREE_COLOR_GROUND():
    img.draw_cross(camerahigh//2,camerawide//2,COLOR_YELLOW,5,1)       #在中心点绘制一个十字
    #红色
    blobs_red=img.find_blobs(red_thresholds,False,x_stride=2,y_stride=1,area_threshold=700,pixels_threshold=700)
    if blobs_red :
        for blob1 in blobs_red:
            if blob1[3]<MAX_PAN and blob1[2]<MAX_PAN:
                max_red = find_max(blobs_red)
                cx2, cy2,max_red_w,max_red_h = max_red.cx(), max_red.cy(),max_red.w(), max_red.h(),     # 假设 cx 和 cy 是元组的最后两个元素
                img.draw_rect(cx2-max_red_w//2, cy2-max_red_h//2, max_red_w, max_red_h, image.COLOR_PURPLE) #在图像上绘制一个紫色矩形框，框住最大的红色blob
                img.draw_cross(cx2, cy2,COLOR_PURPLE,5,1)       #在中心点绘制一个紫色十字
                ser.write(bytes([red_byte]))        #通过串口发送红色包头red_byte
                red_x=blob1[0]+blob1[2]//2+GROUND_CENERY_X      #计算最大红色blob的中心点坐标，并加上地面场景的坐标偏移量
                red_Y=blob1[1]+blob1[3]//2+GROUND_CENERY_Y
                red_centry = f"{red_x},{red_Y}\n"       #将坐标转换为字符串red_centry
                ser.write(red_centry.encode())          #通过串口发送
                img.draw_string(0, 0,"b %d,%d"%(red_x,red_Y), color = image.COLOR_RED,scale=1)
                print(red_x,red_Y)      #打印坐标信息
    #绿色
    blobs_green=img.find_blobs(green_thresholds,False,x_stride=2,y_stride=1,area_threshold=500,pixels_threshold=500)
    if blobs_green :
        for blob2 in blobs_green:
            if blob2[3]<MAX_PAN and blob2[2]<MAX_PAN:
                max_green = find_max(blobs_green)
                cx1, cy1,max_green_w,max_green_h = max_green.cx(), max_green.cy(),max_green.w(), max_green.h()# 假设 cx 和 cy 是元组的最后两个元素
                img.draw_rect(cx1-max_green_w//2, cy1-max_green_h//2, max_green_w, max_green_h, image.COLOR_GREEN)
                img.draw_cross(cx1, cy1,COLOR_GREEN,5,1)
                green_x=cx1+GROUND_CENERY_X
                green_y=cy1+GROUND_CENERY_Y
                ser.write(bytes([green_byte]))
                green_centry= f"{green_x},{green_y}\n"
                ser.write(green_centry.encode())
                img.draw_string(0, 0,"b %d,%d"%(green_x,green_y), color = image.COLOR_RED,scale=1)
                print(green_x,green_y)
    #蓝色
    blobs_blue=img.find_blobs(blue_thresholeds,False,x_stride=2,y_stride=1,area_threshold=700,pixels_threshold=700)
    if blobs_blue:    
        for blob3 in blobs_blue:
            if blob3[3]<MAX_PAN and blob3[2]<MAX_PAN:
                max_blue = find_max(blobs_blue)
                cx3, cy3,max_blue_w,max_blue_h = max_blue.cx(), max_blue.cy(),max_blue.w(), max_blue.h()
                img.draw_rect(cx3-max_blue_w//2, cy3-max_blue_h//2,max_blue_w,max_blue_h,image.COLOR_BLUE)
                img.draw_cross(cx3, cy3,COLOR_BLUE,5,1)
                blue_x=cx3+GROUND_CENERY_X
                blue_y=cy3+GROUND_CENERY_Y
                ser.write(bytes([blue_byte]))
                blue_centry= f"{blue_x},{blue_y}\n"
                ser.write(blue_centry.encode())
                img.draw_string(0, 0,"b %d,%d"%(blue_x,blue_y), color = image.COLOR_RED,scale=1)
                print(blue_x,blue_y)

#用于在平移场景下识别红、绿、蓝三种颜色的物体
#逻辑与FIND_THREE_COLOR_GROUND类似，只是尺寸过滤条件改为MAX_GROUND，坐标偏移量改为PAN_CENERY_X和PAN_CENERY_Y
def FIND_THREE_COLOR_PAN():
    img.draw_cross(camerahigh//2,camerawide//2,COLOR_YELLOW,5,1)       #在中心点绘制一个十字
    #红色
    blobs_red=img.find_blobs(red_thresholds,False,x_stride=2,y_stride=1,area_threshold=700,pixels_threshold=700)
    if blobs_red :
        for blob1 in blobs_red:
            if blob1[3]<MAX_GROUND and blob1[2]<MAX_GROUND:
                max_red = find_max(blobs_red)
                cx2, cy2,max_red_w,max_red_h = max_red.cx(), max_red.cy(),max_red.w(), max_red.h(), # 假设 cx 和 cy 是元组的最后两个元素
                img.draw_rect(cx2-max_red_w//2, cy2-max_red_h//2, max_red_w, max_red_h, image.COLOR_PURPLE)
                img.draw_cross(cx2, cy2,COLOR_PURPLE,5,1)
                ser.write(bytes([red_byte]))
                red_x=blob1[0]+blob1[2]//2+PAN_CENERY_X
                red_Y=blob1[1]+blob1[3]//2+PAN_CENERY_Y
                red_centry = f"{red_x},{red_Y}\n"
                ser.write(red_centry.encode())
                img.draw_string(0, 0,"b %d,%d"%(red_x,red_Y), color = image.COLOR_RED,scale=1)
                print(red_x,red_Y)
    #绿色
    blobs_green=img.find_blobs(green_thresholds,False,x_stride=2,y_stride=1,area_threshold=500,pixels_threshold=500)
    if blobs_green :
        for blob2 in blobs_green:
            if blob2[3]<MAX_GROUND and blob2[2]<MAX_GROUND:
                max_green = find_max(blobs_green)
                cx1, cy1,max_green_w,max_green_h = max_green.cx(), max_green.cy(),max_green.w(), max_green.h()# 假设 cx 和 cy 是元组的最后两个元素
                img.draw_rect(cx1-max_green_w//2, cy1-max_green_h//2, max_green_w, max_green_h, image.COLOR_GREEN)
                img.draw_cross(cx1, cy1,COLOR_GREEN,5,1)
                green_x=cx1+PAN_CENERY_X
                green_y=cy1+PAN_CENERY_Y
                ser.write(bytes([green_byte]))
                green_centry= f"{green_x},{green_y}\n"
                ser.write(green_centry.encode())
                img.draw_string(0, 0,"b %d,%d"%(green_x,green_y), color = image.COLOR_RED,scale=1)
                print(green_x,green_y)
    #蓝色
    blobs_blue=img.find_blobs(blue_thresholeds,False,x_stride=2,y_stride=1,area_threshold=700,pixels_threshold=700)
    if blobs_blue:    
        for blob3 in blobs_blue:
            if blob3[3]<MAX_GROUND and blob3[2]<MAX_GROUND:
                max_blue = find_max(blobs_blue)
                cx3, cy3,max_blue_w,max_blue_h = max_blue.cx(), max_blue.cy(),max_blue.w(), max_blue.h()
                img.draw_rect(cx3-max_blue_w//2, cy3-max_blue_h//2,max_blue_w,max_blue_h,image.COLOR_BLUE)
                img.draw_cross(cx3, cy3,COLOR_BLUE,5,1)
                blue_x=cx3+PAN_CENERY_X
                blue_y=cy3+PAN_CENERY_Y
                ser.write(bytes([blue_byte]))
                blue_centry= f"{blue_x},{blue_y}\n"
                ser.write(blue_centry.encode())
                img.draw_string(0, 0,"b %d,%d"%(blue_x,blue_y), color = image.COLOR_RED,scale=1)
                print(blue_x,blue_y)


centrey_circle_x=-94        #定义圆环识别时的X坐标偏移量
centrey_circle_y=-75        #定义圆环识别时的Y坐标偏移量


#用于识别红、绿、蓝三种颜色的圆环
def FIND_THREE_COLOR_CIRCLE():
    img.draw_cross(-centrey_circle_x,-centrey_circle_y,COLOR_WHITE,5,1)       #在中心点绘制一个紫色十字
    camera_high = 160
    camera_wide = 140
    for obj in objs:
        img.draw_rect(obj.x, obj.y, obj.w, obj.h, color = image.COLOR_RED)  #在图像上绘制红色矩形框
        msg = f'{detector.labels[obj.class_id]}: {obj.score:.2f}'
        img.draw_string(obj.x, obj.y, msg, color = image.COLOR_RED)     #在左上角绘制目标的类别和置信度信息
        #识别到红色圆环
        if detector.labels[obj.class_id]== "{:>1}".format(1):
            if obj.score>0.7:       #判断该目标的置信度是否大于 0.7，如果满足条件，则认为该目标是可靠的红色圆环
                ser.write(bytes([red_circle_byte]))     #通过串口 ser 发送红色圆环的包头 red_circle_byte，用于告知接收方接下来的数据是关于红色圆环的
                sent_red_circle=f"{obj.x+obj.w//2+centrey_circle_x},{obj.y+obj.h//2+centrey_circle_y}\n"        #计算红色圆环的中心点坐标
                img.draw_cross(obj.x+obj.w//2,obj.y+obj.h//2,COLOR_RED,5,1)     #绘制一个红色的十字标记
                ser.write(sent_red_circle.encode())     #将格式化好的中心点坐标字符串编码为字节流，并通过串口发送
                img.draw_string(0, 0,"r %d,%d"%(obj.x+obj.w//2+centrey_circle_x,obj.y+obj.h//2+centrey_circle_y), color = image.COLOR_RED,scale=1)
                print(obj.x+obj.w//2+centrey_circle_x,obj.y+obj.h//2+centrey_circle_y)     #打印红色圆环的中心点坐标
        #识别到绿色圆环      
        if detector.labels[obj.class_id]== "{:>1}".format(2):
            if obj.score>0.7:
                ser.write(bytes([green_cirecle_byte]))
                sent_green_circle=f"{obj.x+obj.w//2+centrey_circle_x},{obj.y+obj.h//2+centrey_circle_y}\n"
                img.draw_cross(obj.x+obj.w//2,obj.y+obj.h//2,COLOR_GREEN,5,1)
                ser.write(sent_green_circle.encode())
                img.draw_string(0, 0,"g %d,%d"%(obj.x+obj.w//2+centrey_circle_x,obj.y+obj.h//2+centrey_circle_y), color = image.COLOR_RED,scale=1)
                print(obj.x+obj.w//2+centrey_circle_x,obj.y+obj.h//2+centrey_circle_y)
        #识别到蓝色圆环
        if detector.labels[obj.class_id]== "{:>1}".format(3):
            if obj.score>0.7:
                ser.write(bytes([blue_circle_byte]))
                sent_blue_circle=f"{obj.x+obj.w//2+centrey_circle_x},{obj.y+obj.h//2+centrey_circle_y}\n"
                img.draw_cross(obj.x+obj.w//2,obj.y+obj.h//2,COLOR_BLUE,5,1)
                ser.write(sent_blue_circle.encode())
                img.draw_string(0, 0,"b %d,%d"%(obj.x+obj.w//2+centrey_circle_x,obj.y+obj.h//2+centrey_circle_y), color = image.COLOR_RED,scale=1)
                print(obj.x+obj.w//2+centrey_circle_x,obj.y+obj.h//2+centrey_circle_y)


cammand=0       #用于存储从串口接收到的上位机指令，初始值设为 0
mode_1=0        #初始化四个模式状态变量
mode_2=0        #用于控制不同的工作模式
mode_3=0        #0表示未激活
mode_4=0        #1表示未激活
#用于根据接收到的串口指令更新模式状态变量
def get_state(cammand):
    global mode_1, mode_2,mode_3,mode_4     #声明全局变量
    if cammand == b'11': mode_1=1
    if cammand == b'01': mode_1=0

    if cammand == b'12': mode_2=1
    if cammand == b'02': mode_2=0

    if cammand == b'13': mode_3=1
    if cammand == b'03': mode_3=0

    if cammand == b'14': mode_4=1
    if cammand == b'04': mode_4=0


while True:
    img= cam.read()         #从相机读取一帧图像
    objs = detector.detect(img, conf_th = 0.60, iou_th = 0.45)  #使用之前初始化的detector对读取到的图像进行目标检测
                #设置置信度阈值大于 0.60 的目标才会被保留   #设置交并比（IoU）阈值为 0.45，用于非极大值抑制（NMS）去除重叠度较高的检测框
    #h获取上位机指令
    cammand = ser.read()        #从串口读取上位机发送的指令，并将其存储在变量 cammand 中
    get_state(cammand)          #根据接收到的指令 cammand 更新模式状态变量
    if mode_1==1:
        while mode_1==1:
            img= cam.read()         #从相机读取一帧图像
            objs = detector.detect(img, conf_th = 0.60, iou_th = 0.45)  #使用之前初始化的detector对读取到的图像进行目标检测
                #设置置信度阈值大于 0.60 的目标才会被保留   #设置交并比（IoU）阈值为 0.45，用于非极大值抑制（NMS）去除重叠度较高的检测框
            cammand = ser.read()        #从串口读取上位机发送的指令，并将其存储在变量 cammand 中
            get_state(cammand)          #根据接收到的指令 cammand 更新模式状态变量
            FIND_THREE_COLOR_PAN()      #平移场景下的颜色识别
            disp.show(img)              #将处理后的图像 img 显示出来
            if mode_1==0: break
 
    if mode_2==1:
        while mode_2==1:
            img= cam.read()         #从相机读取一帧图像
            objs = detector.detect(img, conf_th = 0.60, iou_th = 0.45)  #使用之前初始化的detector对读取到的图像进行目标检测
                #设置置信度阈值大于 0.60 的目标才会被保留   #设置交并比（IoU）阈值为 0.45，用于非极大值抑制（NMS）去除重叠度较高的检测框
            cammand = ser.read()        #从串口读取上位机发送的指令，并将其存储在变量 cammand 中
            get_state(cammand)          #根据接收到的指令 cammand 更新模式状态变量
            FIND_THREE_COLOR_GROUND()   #地面场景下的颜色识别
            disp.show(img)              #将处理后的图像 img 显示出来
            if mode_2==0: break

    if mode_3==1:
        while mode_3==1:
            img= cam.read()         #从相机读取一帧图像
            objs = detector.detect(img, conf_th = 0.60, iou_th = 0.45)  #使用之前初始化的detector对读取到的图像进行目标检测
                #设置置信度阈值大于 0.60 的目标才会被保留   #设置交并比（IoU）阈值为 0.45，用于非极大值抑制（NMS）去除重叠度较高的检测框
            cammand = ser.read()        #从串口读取上位机发送的指令，并将其存储在变量 cammand 中
            get_state(cammand)          #根据接收到的指令 cammand 更新模式状态变量
            FIND_THREE_COLOR_CIRCLE()   #圆环识别
            disp.show(img)              #将处理后的图像 img 显示出来
            if mode_3==0: break

