#include "pch.h"
#include "MainPage.xaml.h"


using namespace App5;
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;


MainPage::MainPage()
{
	InitializeComponent();
    startHandler = ref new RoutedEventHandler(this, &MainPage::Start);
    startToken = testbutton->Click += startHandler;

     //订阅窗口大小变化事件
    windowSizeChangedToken = Window::Current->SizeChanged +=
        ref new WindowSizeChangedEventHandler(
            this, &MainPage::OnWindowSizeChanged
        );

    // 初始化定时器
    timer = ref new DispatcherTimer();
    timer->Interval = TimeSpan{ 10000000 }; 
    timer->Tick += ref new EventHandler<Object^>(this, &MainPage::OnTimerTick);

    // 初始化倒计时时间
    remainingTime = 30;
}

void MainPage::PositionButtonAtCenter()
{
    if (MainCanvas != nullptr && testbutton != nullptr)
    {
        // 获取Canvas的实际尺寸
        double canvasWidth = MainCanvas->ActualWidth;
        double canvasHeight = MainCanvas->ActualHeight;

        // 获取按钮的实际尺寸
        double buttonWidth = testbutton->ActualWidth;
        double buttonHeight = testbutton->ActualHeight;

        // 计算居中位置
        double centerLeft = (canvasWidth - buttonWidth) / 2;
        double centerTop = (canvasHeight - buttonHeight) / 2;

        // 设置初始位置
        Canvas::SetLeft(testbutton, centerLeft);
        Canvas::SetTop(testbutton, centerTop);
    }
}

void App5::MainPage::OnWindowSizeChanged(Platform::Object^ sender,Windows::UI::Core::WindowSizeChangedEventArgs^ e)

{
    Update_Button_Location(nullptr, nullptr);
}


void App5::MainPage::Update_Button_Location(Platform::Object^ sender, RoutedEventArgs^ e) {
    // 获取Canvas的实际尺寸
    double canvasWidth = MainCanvas->ActualWidth;
    double canvasHeight = MainCanvas->ActualHeight;

    // 获取按钮的实际尺寸
    double buttonWidth = testbutton->ActualWidth;
    double buttonHeight = testbutton->ActualHeight;

    // 确保按钮不会超出Canvas边界
    double maxLeft = canvasWidth - buttonWidth;
    double maxTop = canvasHeight - buttonHeight;

    // 使用静态随机数引擎和分布
    static std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<double> leftDist(0.0, maxLeft > 0 ? maxLeft : 0);
    std::uniform_real_distribution<double> topDist(0.0, maxTop > 0 ? maxTop : 0);

    // 生成随机位置
    double left = leftDist(gen);
    double top = topDist(gen);

    // 使用Canvas的附加属性更新位置
    Canvas::SetLeft(testbutton, left);
    Canvas::SetTop(testbutton, top);
}


void App5::MainPage::Start(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e) {
    testbutton->Content = "Click Me!";
    testbutton->Click -= startToken;
    ClickToken = testbutton->Click += ref new RoutedEventHandler(this,&MainPage::Button_Click);
    count = 0;
    Count_Text->Text = "分数："+count.ToString();
    Update_Button_Location(nullptr, nullptr);
    StartCountdown();

}

void App5::MainPage::Stop() {
    testbutton->Click -= ClickToken;
    testbutton->Click += startHandler;
    testbutton->Content = "Start again!";
}

void App5::MainPage::Button_Click(Platform::Object^ sender, RoutedEventArgs^ e)
{
    count++;
    Count_Text->Text = "分数：" + count.ToString();
    Update_Button_Location(nullptr, nullptr);  
   
}


void App5::MainPage::testbutton_Loaded(Platform::Object^ sender, RoutedEventArgs^ e)
{
    PositionButtonAtCenter();
}

// 启动倒计时
void MainPage::StartCountdown()
{
    if (!timer->IsEnabled)
    {
        Time_Text->Text = "倒计时："+remainingTime.ToString()+"秒";
        timer->Start();
    }

}

// 停止倒计时
void MainPage::StopCountdown()
{
    if (timer->IsEnabled)
    {
        timer->Stop();
    }
    Stop();
    PositionButtonAtCenter();
    remainingTime = 5;
}

// 定时器 Tick 事件
void MainPage::OnTimerTick(Platform::Object^ sender, Platform::Object^ e)
{
    if (remainingTime > 0)
    {
        remainingTime--; // 减少剩余时间
        Time_Text->Text = "倒计时：" + remainingTime.ToString() + "秒"; // 更新 UI
    }
    else
    {
        StopCountdown(); // 倒计时结束，停止定时器
        Time_Text->Text = "Time's up!"; // 显示结束信息
    }
}







