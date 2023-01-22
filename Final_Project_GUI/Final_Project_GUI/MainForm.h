#pragma once
#include <iostream>
#include <msclr\marshal_cppstd.h>
#include <string>
#include <ctime>

namespace FinalProjectGUI {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Diagnostics;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace msclr::interop;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}
	
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ lblDashboard;
	private: System::Windows::Forms::Button^ btnDetect;

	private: System::Windows::Forms::Button^ btnLiquidate;
	private: System::Windows::Forms::TextBox^ tbConsoleDetect;
	private: System::Windows::Forms::TextBox^ tbConsoleLiquidate;
	private: System::Windows::Forms::Label^ lblDate;


	protected:

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->lblDashboard = (gcnew System::Windows::Forms::Label());
			this->btnDetect = (gcnew System::Windows::Forms::Button());
			this->btnLiquidate = (gcnew System::Windows::Forms::Button());
			this->tbConsoleDetect = (gcnew System::Windows::Forms::TextBox());
			this->tbConsoleLiquidate = (gcnew System::Windows::Forms::TextBox());
			this->lblDate = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// lblDashboard
			// 
			this->lblDashboard->BackColor = System::Drawing::Color::SteelBlue;
			this->lblDashboard->Font = (gcnew System::Drawing::Font(L"Verdana", 17.25F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblDashboard->ForeColor = System::Drawing::SystemColors::Window;
			this->lblDashboard->Location = System::Drawing::Point(0, 0);
			this->lblDashboard->Name = L"lblDashboard";
			this->lblDashboard->Size = System::Drawing::Size(886, 561);
			this->lblDashboard->TabIndex = 0;
			this->lblDashboard->Text = L"Dashboard";
			// 
			// btnDetect
			// 
			this->btnDetect->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->btnDetect->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnDetect->Location = System::Drawing::Point(205, 39);
			this->btnDetect->Name = L"btnDetect";
			this->btnDetect->Size = System::Drawing::Size(165, 45);
			this->btnDetect->TabIndex = 1;
			this->btnDetect->Text = L"Start Detection";
			this->btnDetect->UseVisualStyleBackColor = true;
			this->btnDetect->Click += gcnew System::EventHandler(this, &MainForm::btnDetect_Click);
			// 
			// btnLiquidate
			// 
			this->btnLiquidate->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->btnLiquidate->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnLiquidate->Location = System::Drawing::Point(668, 39);
			this->btnLiquidate->Name = L"btnLiquidate";
			this->btnLiquidate->Size = System::Drawing::Size(157, 45);
			this->btnLiquidate->TabIndex = 2;
			this->btnLiquidate->Text = L"Liquidate";
			this->btnLiquidate->UseVisualStyleBackColor = true;
			this->btnLiquidate->Click += gcnew System::EventHandler(this, &MainForm::btnLiquidate_Click);
			// 
			// tbConsoleDetect
			// 
			this->tbConsoleDetect->BackColor = System::Drawing::Color::Black;
			this->tbConsoleDetect->ForeColor = System::Drawing::Color::White;
			this->tbConsoleDetect->Location = System::Drawing::Point(0, 90);
			this->tbConsoleDetect->Multiline = true;
			this->tbConsoleDetect->Name = L"tbConsoleDetect";
			this->tbConsoleDetect->ReadOnly = true;
			this->tbConsoleDetect->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->tbConsoleDetect->Size = System::Drawing::Size(597, 471);
			this->tbConsoleDetect->TabIndex = 3;
			// 
			// tbConsoleLiquidate
			// 
			this->tbConsoleLiquidate->BackColor = System::Drawing::Color::Black;
			this->tbConsoleLiquidate->ForeColor = System::Drawing::Color::White;
			this->tbConsoleLiquidate->Location = System::Drawing::Point(603, 90);
			this->tbConsoleLiquidate->Multiline = true;
			this->tbConsoleLiquidate->Name = L"tbConsoleLiquidate";
			this->tbConsoleLiquidate->ReadOnly = true;
			this->tbConsoleLiquidate->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->tbConsoleLiquidate->Size = System::Drawing::Size(281, 471);
			this->tbConsoleLiquidate->TabIndex = 4;
			// 
			// lblDate
			// 
			this->lblDate->BackColor = System::Drawing::Color::SteelBlue;
			this->lblDate->Font = (gcnew System::Drawing::Font(L"Verdana", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblDate->ForeColor = System::Drawing::Color::White;
			this->lblDate->Location = System::Drawing::Point(747, 1);
			this->lblDate->Name = L"lblDate";
			this->lblDate->Size = System::Drawing::Size(135, 23);
			this->lblDate->TabIndex = 5;
			this->lblDate->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(884, 561);
			this->Controls->Add(this->lblDate);
			this->Controls->Add(this->tbConsoleLiquidate);
			this->Controls->Add(this->tbConsoleDetect);
			this->Controls->Add(this->btnLiquidate);
			this->Controls->Add(this->btnDetect);
			this->Controls->Add(this->lblDashboard);
			this->MaximumSize = System::Drawing::Size(900, 600);
			this->MinimumSize = System::Drawing::Size(900, 600);
			this->Name = L"MainForm";
			this->Text = L"Real Time Detection of Aerostats with Drones";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion	
	int Main_Program()
	{
		// Specify the path to the exe file
		String^ exePath = "balloons_detection.exe";
		msclr::interop::marshal_context context;
		std::string command = context.marshal_as<std::string>(exePath);

		// Start the exe file
		Process^ process = gcnew Process();
		process->StartInfo->FileName = exePath;
		process->StartInfo->UseShellExecute = false;
		process->StartInfo->RedirectStandardOutput = true;
		process->Start();

		// Read the output of the exe file in real-time
		while (!process->StandardOutput->EndOfStream)
		{
			String^ output = process->StandardOutput->ReadLine();
			tbConsoleDetect->AppendText(output + Environment::NewLine);
			Application::DoEvents();
		}

		return -1;
	}

	private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
		btnLiquidate->Visible = false;
		tbConsoleLiquidate->Visible = false;

		DateTime now = DateTime::Now;
		lblDate->Text = now.ToString("dd/MM/yyyy");
	}

	private: System::Void btnDetect_Click(System::Object^ sender, System::EventArgs^ e) {
		btnLiquidate->Visible = true;
		tbConsoleLiquidate->Visible = true;

		Main_Program();
	}

	private: System::Void btnLiquidate_Click(System::Object^ sender, System::EventArgs^ e) {
	}
};
}
