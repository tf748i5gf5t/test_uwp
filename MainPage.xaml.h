//
// MainPage.xaml.h
// MainPage 类的声明。
//

#pragma once
#include "MainPage.g.h"

namespace App5
{
	/// <summary>
	/// 可用于自身或导航至 Frame 内部的空白页。
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();
		void PositionButtonAtCenter();

	private:
		int count ;
		Windows::UI::Xaml::RoutedEventHandler^ startHandler;
		Windows::Foundation::EventRegistrationToken startToken;
		void Start(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Stop();

		Windows::Foundation::EventRegistrationToken ClickToken;
		void Button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void testbutton_Loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Update_Button_Location(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);

		// 声明窗口大小变化事件处理函数
		void OnWindowSizeChanged(Platform::Object^ sender, Windows::UI::Core::WindowSizeChangedEventArgs^ e);

		// 声明事件处理Token（用于安全取消订阅）
		Windows::Foundation::EventRegistrationToken windowSizeChangedToken;
		

		Windows::UI::Xaml::DispatcherTimer^ timer; // 定时器
		int remainingTime; // 剩余时间（秒）
		void StartCountdown(); // 启动倒计时
		void StopCountdown();  // 停止倒计时
		void OnTimerTick(Platform::Object^ sender, Platform::Object^ e);
		
		
	};


}
