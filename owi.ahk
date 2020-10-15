SetTitleMatchMode, 2
DetectHiddenWindows, On
epid := WinExist("Epic Pen")
owid := WinExist("ahk_class TankWindowClass")
cstate = 1 ; 1 - view mode, 2 - edit mode
istate = 1 ; 1 - controls on, 2 - controls off
pstate = 1 ; 1 - pause on, 2 - pause off

; Self controls

CapsLock::switch_modes()
^z::clear_and_view()
^x::clear_and_continue_replay()
^c::pause_and_edit()
~^s::switch_playback_state()

^!k::Suspend On
^!j::Suspend Off
^!l::reload_this_script()

; Overwatch controls

send_toggle_ui() {
    Send ^d
}

send_toggle_play() {
    Send ^s
}

; Epic Pen controls

send_toggle_pencil() {
    Send ^w
}

send_toggle_clear() {
    Send ^q
}

send_toggle_cursor() {
    Send ^e
}

; APPLICATION 

reload_this_script() {
    MsgBox Reloading!
    Reload
}

switch_playback_state() {
    if (WinActive("ahk_class TankWindowClass")) {
        global pstate
        if (pstate == 1) {
            pstate = 2
        } else {
            pstate = 1
        }
    }
}

in_pencil() {
    global epid    
    WinActivate, ahk_id %epid%
    WinWaitActive, ahk_id %epid%
}

in_ow() {
    global owid    
    WinActivate, ahk_id %owid%
    WinWaitActive, ahk_id %owid%    
}

editmode()
{  
    global epid
    global owid
    global cstate
    global istate

    RunWait "bin/owi.exe",,Hide
    sleep, 100

    if ("0" == %clipboard%) {
        istate = 2
        WinActivate, ahk_id %owid%
        send_toggle_ui()
    }

    WinActivate, ahk_id %epid%
    send_toggle_pencil()
}

viewmode()
{
    global epid
    global owid
    global cstate
    global istate

    send_toggle_cursor()

	WinActivate, ahk_id %owid%
    WinWaitActive, ahk_id %owid%
    if (istate == 2) {
        istate = 1
        send_toggle_ui()
    }
}

clear_and_continue_replay() {
   global cstate
   global pstate
   cstate := 1

   in_pencil()
   send_toggle_clear()
   viewmode()

   MsgBox %pstate%
   if (pstate == 1) {
        pstate = 2
        send_toggle_play()
   } 
}

clear_and_view() {
   global cstate
   cstate := 1

   in_pencil()
   send_toggle_clear()
   viewmode()
}

pause_and_edit() {
    global cstate
    global pstate
    cstate := 2 

    in_ow()
    MsgBox %pstate%
    if (pstate == 2) {
        pstate = 1
        send_toggle_play()
    }
    
    in_pencil()
    editmode()
}

switch_modes() {
    global cstate
    if (cstate = 1) {
        cstate := 2
        editmode()
    } else {
        cstate := 1
        viewmode()
    }
}

Return