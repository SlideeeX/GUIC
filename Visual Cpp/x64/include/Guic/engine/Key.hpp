#pragma once
#include <Guic/engine/Keys.hpp>
#include <Guic/engine/KeyCode.hpp>

namespace guic { namespace engine {

constexpr Keys makeKey(KeyCode keyCode)
{
    return Keys(static_cast<Uint16>(keyCode));
}

namespace key { namespace Key {

    constexpr Keys Unknown = makeKey(KeyCode::Unknown);

    constexpr Keys A = makeKey(KeyCode::A);
    constexpr Keys B = makeKey(KeyCode::B);
    constexpr Keys C = makeKey(KeyCode::C);
    constexpr Keys D = makeKey(KeyCode::D);
    constexpr Keys E = makeKey(KeyCode::E);
    constexpr Keys F = makeKey(KeyCode::F);
    constexpr Keys G = makeKey(KeyCode::G);
    constexpr Keys H = makeKey(KeyCode::H);
    constexpr Keys I = makeKey(KeyCode::I);
    constexpr Keys J = makeKey(KeyCode::J);
    constexpr Keys K = makeKey(KeyCode::K);
    constexpr Keys L = makeKey(KeyCode::L);
    constexpr Keys M = makeKey(KeyCode::M);
    constexpr Keys N = makeKey(KeyCode::N);
    constexpr Keys O = makeKey(KeyCode::O);
    constexpr Keys P = makeKey(KeyCode::P);
    constexpr Keys Q = makeKey(KeyCode::Q);
    constexpr Keys R = makeKey(KeyCode::R);
    constexpr Keys S = makeKey(KeyCode::S);
    constexpr Keys T = makeKey(KeyCode::T);
    constexpr Keys U = makeKey(KeyCode::U);
    constexpr Keys V = makeKey(KeyCode::V);
    constexpr Keys W = makeKey(KeyCode::W);
    constexpr Keys X = makeKey(KeyCode::X);
    constexpr Keys Y = makeKey(KeyCode::Y);
    constexpr Keys Z = makeKey(KeyCode::Z);

    constexpr Keys D1 = makeKey(KeyCode::D1);
    constexpr Keys D2 = makeKey(KeyCode::D2);
    constexpr Keys D3 = makeKey(KeyCode::D3);
    constexpr Keys D4 = makeKey(KeyCode::D4);
    constexpr Keys D5 = makeKey(KeyCode::D5);
    constexpr Keys D6 = makeKey(KeyCode::D6);
    constexpr Keys D7 = makeKey(KeyCode::D7);
    constexpr Keys D8 = makeKey(KeyCode::D8);
    constexpr Keys D9 = makeKey(KeyCode::D9);
    constexpr Keys D0 = makeKey(KeyCode::D0);

    constexpr Keys Return = makeKey(KeyCode::Return);
    constexpr Keys Escape = makeKey(KeyCode::Escape);
    constexpr Keys Backspace = makeKey(KeyCode::Backspace);
    constexpr Keys Tab = makeKey(KeyCode::Tab);
    constexpr Keys Space = makeKey(KeyCode::Space);

    constexpr Keys Minus = makeKey(KeyCode::Minus);
    constexpr Keys Equals = makeKey(KeyCode::Equals);
    constexpr Keys LeftBracket = makeKey(KeyCode::LeftBracket);
    constexpr Keys RightBracket = makeKey(KeyCode::RightBracket);
    constexpr Keys Backslash = makeKey(KeyCode::Backslash);
    constexpr Keys NonUSHash = makeKey(KeyCode::NonUSHash);
    constexpr Keys Semicolon = makeKey(KeyCode::Semicolon);
    constexpr Keys Apostrophe = makeKey(KeyCode::Apostrophe);
    constexpr Keys Grave = makeKey(KeyCode::Grave);
    constexpr Keys Comma = makeKey(KeyCode::Comma);
    constexpr Keys Period = makeKey(KeyCode::Period);
    constexpr Keys Slash = makeKey(KeyCode::Slash);

    constexpr Keys CapsLock = makeKey(KeyCode::CapsLock);

    constexpr Keys F1 = makeKey(KeyCode::F1);
    constexpr Keys F2 = makeKey(KeyCode::F2);
    constexpr Keys F3 = makeKey(KeyCode::F3);
    constexpr Keys F4 = makeKey(KeyCode::F4);
    constexpr Keys F5 = makeKey(KeyCode::F5);
    constexpr Keys F6 = makeKey(KeyCode::F6);
    constexpr Keys F7 = makeKey(KeyCode::F7);
    constexpr Keys F8 = makeKey(KeyCode::F8);
    constexpr Keys F9 = makeKey(KeyCode::F9);
    constexpr Keys F10 = makeKey(KeyCode::F10);
    constexpr Keys F11 = makeKey(KeyCode::F11);
    constexpr Keys F12 = makeKey(KeyCode::F12);

    constexpr Keys Insert = makeKey(KeyCode::Insert);
    constexpr Keys Home = makeKey(KeyCode::Home);
    constexpr Keys PageUp = makeKey(KeyCode::PageUp);
    constexpr Keys Delete = makeKey(KeyCode::Delete);
    constexpr Keys End = makeKey(KeyCode::End);
    constexpr Keys PageDown = makeKey(KeyCode::PageDown);

    constexpr Keys Right = makeKey(KeyCode::Right);
    constexpr Keys Left = makeKey(KeyCode::Left);
    constexpr Keys Down = makeKey(KeyCode::Down);
    constexpr Keys Up = makeKey(KeyCode::Up);

    constexpr Keys NumLock = makeKey(KeyCode::NumLock);
    constexpr Keys Num0 = makeKey(KeyCode::Num0);
    constexpr Keys Num1 = makeKey(KeyCode::Num1);
    constexpr Keys Num2 = makeKey(KeyCode::Num2);
    constexpr Keys Num3 = makeKey(KeyCode::Num3);
    constexpr Keys Num4 = makeKey(KeyCode::Num4);
    constexpr Keys Num5 = makeKey(KeyCode::Num5);
    constexpr Keys Num6 = makeKey(KeyCode::Num6);
    constexpr Keys Num7 = makeKey(KeyCode::Num7);
    constexpr Keys Num8 = makeKey(KeyCode::Num8);
    constexpr Keys Num9 = makeKey(KeyCode::Num9);
    constexpr Keys NumEnter = makeKey(KeyCode::NumEnter);
    constexpr Keys NumPlus = makeKey(KeyCode::NumPlus);
    constexpr Keys NumMinus = makeKey(KeyCode::NumMinus);
    constexpr Keys NumMultiply = makeKey(KeyCode::NumMultiply);
    constexpr Keys NumDivide = makeKey(KeyCode::NumDivide);
    constexpr Keys NumPeriod = makeKey(KeyCode::NumPeriod);
    constexpr Keys NumEquals = makeKey(KeyCode::NumEquals);

    constexpr Keys PrintScreen = makeKey(KeyCode::PrintScreen);
    constexpr Keys ScrollLock = makeKey(KeyCode::ScrollLock);
    constexpr Keys Pause = makeKey(KeyCode::Pause);

    constexpr Keys NonUSBackslash = makeKey(KeyCode::NonUSBackslash);
    constexpr Keys Application = makeKey(KeyCode::Application);
    constexpr Keys Power = makeKey(KeyCode::Power);

    constexpr Keys F13 = makeKey(KeyCode::F13);
    constexpr Keys F14 = makeKey(KeyCode::F14);
    constexpr Keys F15 = makeKey(KeyCode::F15);
    constexpr Keys F16 = makeKey(KeyCode::F16);
    constexpr Keys F17 = makeKey(KeyCode::F17);
    constexpr Keys F18 = makeKey(KeyCode::F18);
    constexpr Keys F19 = makeKey(KeyCode::F19);
    constexpr Keys F20 = makeKey(KeyCode::F20);
    constexpr Keys F21 = makeKey(KeyCode::F21);
    constexpr Keys F22 = makeKey(KeyCode::F22);
    constexpr Keys F23 = makeKey(KeyCode::F23);
    constexpr Keys F24 = makeKey(KeyCode::F24);

    constexpr Keys Execute = makeKey(KeyCode::Execute);
    constexpr Keys Help = makeKey(KeyCode::Help);
    constexpr Keys Menu = makeKey(KeyCode::Menu);
    constexpr Keys Select = makeKey(KeyCode::Select);
    constexpr Keys Stop = makeKey(KeyCode::Stop);
    constexpr Keys Again = makeKey(KeyCode::Again);
    constexpr Keys Undo = makeKey(KeyCode::Undo);
    constexpr Keys Cut = makeKey(KeyCode::Cut);
    constexpr Keys Copy = makeKey(KeyCode::Copy);
    constexpr Keys Paste = makeKey(KeyCode::Paste);
    constexpr Keys Find = makeKey(KeyCode::Find);

    constexpr Keys Mute = makeKey(KeyCode::Mute);
    constexpr Keys VolumeUp = makeKey(KeyCode::VolumeUp);
    constexpr Keys VolumeDown = makeKey(KeyCode::VolumeDown);

    constexpr Keys KP_Comma = makeKey(KeyCode::KP_Comma);
    constexpr Keys KP_EqualsAS400 = makeKey(KeyCode::KP_EqualsAS400);

    constexpr Keys International1 = makeKey(KeyCode::International1);
    constexpr Keys International2 = makeKey(KeyCode::International2);
    constexpr Keys International3 = makeKey(KeyCode::International3);
    constexpr Keys International4 = makeKey(KeyCode::International4);
    constexpr Keys International5 = makeKey(KeyCode::International5);
    constexpr Keys International6 = makeKey(KeyCode::International6);
    constexpr Keys International7 = makeKey(KeyCode::International7);
    constexpr Keys International8 = makeKey(KeyCode::International8);
    constexpr Keys International9 = makeKey(KeyCode::International9);

    constexpr Keys LANG1 = makeKey(KeyCode::LANG1);
    constexpr Keys LANG2 = makeKey(KeyCode::LANG2);
    constexpr Keys LANG3 = makeKey(KeyCode::LANG3);
    constexpr Keys LANG4 = makeKey(KeyCode::LANG4);
    constexpr Keys LANG5 = makeKey(KeyCode::LANG5);
    constexpr Keys LANG6 = makeKey(KeyCode::LANG6);
    constexpr Keys LANG7 = makeKey(KeyCode::LANG7);
    constexpr Keys LANG8 = makeKey(KeyCode::LANG8);
    constexpr Keys LANG9 = makeKey(KeyCode::LANG9);

    constexpr Keys AlterEASE = makeKey(KeyCode::AlterEASE);
    constexpr Keys SysReq = makeKey(KeyCode::SysReq);
    constexpr Keys Cancel = makeKey(KeyCode::Cancel);
    constexpr Keys Clear = makeKey(KeyCode::Clear);
    constexpr Keys Prior = makeKey(KeyCode::Prior);
    constexpr Keys Return2 = makeKey(KeyCode::Return2);
    constexpr Keys Separator = makeKey(KeyCode::Separator);
    constexpr Keys Out = makeKey(KeyCode::Out);
    constexpr Keys Oper = makeKey(KeyCode::Oper);
    constexpr Keys ClearAgain = makeKey(KeyCode::ClearAgain);
    constexpr Keys CrSel = makeKey(KeyCode::CrSel);
    constexpr Keys ExSel = makeKey(KeyCode::ExSel);

    constexpr Keys KP_00 = makeKey(KeyCode::KP00);
    constexpr Keys KP_000 = makeKey(KeyCode::KP000);

    constexpr Keys ThousandsSeparator = makeKey(KeyCode::ThousandsSeparator);
    constexpr Keys DecimalSeparator = makeKey(KeyCode::DecimalSeparator);
    constexpr Keys CurrencyUnit = makeKey(KeyCode::CurrencyUnit);
    constexpr Keys CurrencySubUnit = makeKey(KeyCode::CurrencySubUnit);

    constexpr Keys KP_LeftParen = makeKey(KeyCode::KP_LeftParen);
    constexpr Keys KP_RightParen = makeKey(KeyCode::KP_RightParen);
    constexpr Keys KP_LeftBrace = makeKey(KeyCode::KP_LeftBrace);
    constexpr Keys KP_RightBrace = makeKey(KeyCode::KP_RightBrace);

    constexpr Keys KP_Tab = makeKey(KeyCode::KP_Tab);
    constexpr Keys KP_Backspace = makeKey(KeyCode::KP_Backspace);

    constexpr Keys KP_A = makeKey(KeyCode::KP_A);
    constexpr Keys KP_B = makeKey(KeyCode::KP_B);
    constexpr Keys KP_C = makeKey(KeyCode::KP_C);
    constexpr Keys KP_D = makeKey(KeyCode::KP_D);
    constexpr Keys KP_E = makeKey(KeyCode::KP_E);
    constexpr Keys KP_F = makeKey(KeyCode::KP_F);

    constexpr Keys KP_XOR = makeKey(KeyCode::KP_XOR);
    constexpr Keys KP_Power = makeKey(KeyCode::KP_Power);
    constexpr Keys KP_Percent = makeKey(KeyCode::KP_Percent);
    constexpr Keys KP_Less = makeKey(KeyCode::KP_Less);
    constexpr Keys KP_Greater = makeKey(KeyCode::KP_Greater);

    constexpr Keys KP_Ampersand = makeKey(KeyCode::KP_Ampersand);
    constexpr Keys KP_DblAmpersand = makeKey(KeyCode::KP_DblAmpersand);

    constexpr Keys KP_VerticalBar = makeKey(KeyCode::KP_VerticalBar);
    constexpr Keys KP_DblVerticalBar = makeKey(KeyCode::KP_DblVerticalBar);

    constexpr Keys KP_Colon = makeKey(KeyCode::KP_Colon);
    constexpr Keys KP_Hash = makeKey(KeyCode::KP_Hash);
    constexpr Keys KP_Space = makeKey(KeyCode::KP_Space);
    constexpr Keys KP_At = makeKey(KeyCode::KP_At);
    constexpr Keys KP_Exclam = makeKey(KeyCode::KP_Exclam);

    constexpr Keys KP_MemStore = makeKey(KeyCode::KP_MemStore);
    constexpr Keys KP_MemRecall = makeKey(KeyCode::KP_MemRecall);
    constexpr Keys KP_MemClear = makeKey(KeyCode::KP_MemClear);
    constexpr Keys KP_MemAdd = makeKey(KeyCode::KP_MemAdd);
    constexpr Keys KP_MemSubtract = makeKey(KeyCode::KP_MemSubtract);
    constexpr Keys KP_MemMultiply = makeKey(KeyCode::KP_MemMultiply);
    constexpr Keys KP_MemDivide = makeKey(KeyCode::KP_MemDivide);

    constexpr Keys KP_PlusMinus = makeKey(KeyCode::KP_PlusMinus);

    constexpr Keys KP_Clear = makeKey(KeyCode::KP_Clear);
    constexpr Keys KP_ClearEntry = makeKey(KeyCode::KP_ClearEntry);

    constexpr Keys KP_Binary = makeKey(KeyCode::KP_Binary);
    constexpr Keys KP_Octal = makeKey(KeyCode::KP_Octal);
    constexpr Keys KP_Decimal = makeKey(KeyCode::KP_Decimal);
    constexpr Keys KP_Hexadecimal = makeKey(KeyCode::KP_Hexadecimal);

    constexpr Keys Ctrl = makeKey(KeyCode::Ctrl);
    constexpr Keys Shift = makeKey(KeyCode::Shift);
    constexpr Keys Alt = makeKey(KeyCode::Alt);
    constexpr Keys GUI = makeKey(KeyCode::GUI);

    constexpr Keys RCtrl = makeKey(KeyCode::RCtrl);
    constexpr Keys RShift = makeKey(KeyCode::RShift);
    constexpr Keys RAlt = makeKey(KeyCode::RAlt);
    constexpr Keys RGUI = makeKey(KeyCode::RGUI);

    constexpr Keys Mode = makeKey(KeyCode::Mode);
    constexpr Keys Sleep = makeKey(KeyCode::Sleep);

    constexpr Keys AC_Search = makeKey(KeyCode::AC_Search);
    constexpr Keys AC_Home = makeKey(KeyCode::AC_Home);
    constexpr Keys AC_Back = makeKey(KeyCode::AC_Back);
    constexpr Keys AC_Forward = makeKey(KeyCode::AC_Forward);
    constexpr Keys AC_Stop = makeKey(KeyCode::AC_Stop);
    constexpr Keys AC_Refresh = makeKey(KeyCode::AC_Refresh);
    constexpr Keys AC_Bookmarks = makeKey(KeyCode::AC_Bookmarks);

    constexpr Keys SoftLeft = makeKey(KeyCode::SoftLeft);
    constexpr Keys SoftRight = makeKey(KeyCode::SoftRight);
    constexpr Keys Call = makeKey(KeyCode::Call);
    constexpr Keys EndCall = makeKey(KeyCode::EndCall);

    constexpr Keys LMB = makeKey(KeyCode::LeftMouseButton);
    constexpr Keys MMB = makeKey(KeyCode::MiddleMouseButton);
    constexpr Keys RMB = makeKey(KeyCode::RightMouseButton);
    constexpr Keys SideMouseButtonX1 = makeKey(KeyCode::SideMouseButtonX1);
    constexpr Keys SideMouseButtonX2 = makeKey(KeyCode::SideMouseButtonX2);

    constexpr Keys ControllerButtonA = makeKey(KeyCode::ControllerButtonA);
    constexpr Keys ControllerButtonB = makeKey(KeyCode::ControllerButtonB);
    constexpr Keys ControllerButtonX = makeKey(KeyCode::ControllerButtonX);
    constexpr Keys ControllerButtonY = makeKey(KeyCode::ControllerButtonY);
    constexpr Keys ControllerButtonBack = makeKey(KeyCode::ControllerButtonBack);
    constexpr Keys ControllerButtonGuide = makeKey(KeyCode::ControllerButtonGuide);
    constexpr Keys ControllerButtonStart = makeKey(KeyCode::ControllerButtonStart);
    constexpr Keys ControllerButtonLeftStick = makeKey(KeyCode::ControllerButtonLeftStick);
    constexpr Keys ControllerButtonRightStick = makeKey(KeyCode::ControllerButtonRightStick);
    constexpr Keys ControllerButtonLeftShoulder = makeKey(KeyCode::ControllerButtonLeftShoulder);
    constexpr Keys ControllerButtonRightShoulder = makeKey(KeyCode::ControllerButtonRightShoulder);
    constexpr Keys ControllerButtonDpadUp = makeKey(KeyCode::ControllerButtonDpadUp);
    constexpr Keys ControllerButtonDpadDown = makeKey(KeyCode::ControllerButtonDpadDown);
    constexpr Keys ControllerButtonDpadLeft = makeKey(KeyCode::ControllerButtonDpadLeft);
    constexpr Keys ControllerButtonDpadRight = makeKey(KeyCode::ControllerButtonDpadRight);
    constexpr Keys ControllerButtonMisc1 = makeKey(KeyCode::ControllerButtonMisc1);
    constexpr Keys ControllerButtonPaddle1 = makeKey(KeyCode::ControllerButtonPaddle1);
    constexpr Keys ControllerButtonPaddle2 = makeKey(KeyCode::ControllerButtonPaddle2);
    constexpr Keys ControllerButtonPaddle3 = makeKey(KeyCode::ControllerButtonPaddle3);
    constexpr Keys ControllerButtonPaddle4 = makeKey(KeyCode::ControllerButtonPaddle4);
    constexpr Keys ControllerButtonTouchpad = makeKey(KeyCode::ControllerButtonTouchpad);

    namespace Mouse
    {
        constexpr Keys LeftMouseButton = Key::LMB;
        constexpr Keys MiddleMouseButton = Key::MMB;
        constexpr Keys RightMouseButton = Key::RMB;
        constexpr Keys SideMouseButtonX1 = Key::SideMouseButtonX1;
        constexpr Keys SideMouseButtonX2 = Key::SideMouseButtonX2;
    }

    namespace Keyboard
    {
        constexpr Keys A = Key::A;
        constexpr Keys B = Key::B;
        constexpr Keys C = Key::C;
        constexpr Keys D = Key::D;
        constexpr Keys E = Key::E;
        constexpr Keys F = Key::F;
        constexpr Keys G = Key::G;
        constexpr Keys H = Key::H;
        constexpr Keys I = Key::I;
        constexpr Keys J = Key::J;
        constexpr Keys K = Key::K;
        constexpr Keys L = Key::L;
        constexpr Keys M = Key::M;
        constexpr Keys N = Key::N;
        constexpr Keys O = Key::O;
        constexpr Keys P = Key::P;
        constexpr Keys Q = Key::Q;
        constexpr Keys R = Key::R;
        constexpr Keys S = Key::S;
        constexpr Keys T = Key::T;
        constexpr Keys U = Key::U;
        constexpr Keys V = Key::V;
        constexpr Keys W = Key::W;
        constexpr Keys X = Key::X;
        constexpr Keys Y = Key::Y;
        constexpr Keys Z = Key::Z;

        constexpr Keys D0 = Key::D0;
        constexpr Keys D1 = Key::D1;
        constexpr Keys D2 = Key::D2;
        constexpr Keys D3 = Key::D3;
        constexpr Keys D4 = Key::D4;
        constexpr Keys D5 = Key::D5;
        constexpr Keys D6 = Key::D6;
        constexpr Keys D7 = Key::D7;
        constexpr Keys D8 = Key::D8;
        constexpr Keys D9 = Key::D9;

        constexpr Keys Escape = Key::Escape;
        constexpr Keys Tab = Key::Tab;
        constexpr Keys CapsLock = Key::CapsLock;
        constexpr Keys Shift = Key::Shift;
        constexpr Keys Ctrl = Key::Ctrl;
        constexpr Keys Alt = Key::Alt;
        constexpr Keys GUI = Key::GUI;

        constexpr Keys RShift = Key::RShift;
        constexpr Keys RCtrl = Key::RCtrl;
        constexpr Keys RAlt = Key::RAlt;
        constexpr Keys RGUI = Key::RGUI;

        constexpr Keys Space = Key::Space;
        constexpr Keys Return = Key::Return;
        constexpr Keys Backspace = Key::Backspace;

        constexpr Keys Minus = Key::Minus;
        constexpr Keys Equals = Key::Equals;
        constexpr Keys LeftBracket = Key::LeftBracket;
        constexpr Keys RightBracket = Key::RightBracket;
        constexpr Keys Backslash = Key::Backslash;
        constexpr Keys Semicolon = Key::Semicolon;
        constexpr Keys Apostrophe = Key::Apostrophe;
        constexpr Keys Grave = Key::Grave;
        constexpr Keys Comma = Key::Comma;
        constexpr Keys Period = Key::Period;
        constexpr Keys Slash = Key::Slash;

        constexpr Keys PrintScreen = Key::PrintScreen;
        constexpr Keys ScrollLock = Key::ScrollLock;
        constexpr Keys Pause = Key::Pause;

        constexpr Keys Insert = Key::Insert;
        constexpr Keys Delete = Key::Delete;
        constexpr Keys Home = Key::Home;
        constexpr Keys End = Key::End;
        constexpr Keys PageUp = Key::PageUp;
        constexpr Keys PageDown = Key::PageDown;

        constexpr Keys Up = Key::Up;
        constexpr Keys Down = Key::Down;
        constexpr Keys Left = Key::Left;
        constexpr Keys Right = Key::Right;

        constexpr Keys F1 = Key::F1;
        constexpr Keys F2 = Key::F2;
        constexpr Keys F3 = Key::F3;
        constexpr Keys F4 = Key::F4;
        constexpr Keys F5 = Key::F5;
        constexpr Keys F6 = Key::F6;
        constexpr Keys F7 = Key::F7;
        constexpr Keys F8 = Key::F8;
        constexpr Keys F9 = Key::F9;
        constexpr Keys F10 = Key::F10;
        constexpr Keys F11 = Key::F11;
        constexpr Keys F12 = Key::F12;

        constexpr Keys NumLock = Key::NumLock;
        constexpr Keys NumDivide = Key::NumDivide;
        constexpr Keys NumMultiply = Key::NumMultiply;
        constexpr Keys NumMinus = Key::NumMinus;
        constexpr Keys NumPlus = Key::NumPlus;
        constexpr Keys NumEnter = Key::NumEnter;
        constexpr Keys NumPeriod = Key::NumPeriod;

        constexpr Keys Num0 = Key::Num0;
        constexpr Keys Num1 = Key::Num1;
        constexpr Keys Num2 = Key::Num2;
        constexpr Keys Num3 = Key::Num3;
        constexpr Keys Num4 = Key::Num4;
        constexpr Keys Num5 = Key::Num5;
        constexpr Keys Num6 = Key::Num6;
        constexpr Keys Num7 = Key::Num7;
        constexpr Keys Num8 = Key::Num8;
        constexpr Keys Num9 = Key::Num9;
    }
}}

}}
