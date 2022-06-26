use sysinfo::{System, SystemExt, ProcessExt, Pid};
use windows::{Win32::{System::Diagnostics::{ToolHelp::{CreateToolhelp32Snapshot, TH32CS_SNAPMODULE32, TH32CS_SNAPMODULE}}, Foundation::HANDLE}};

pub fn get_process_list() -> Vec<(Pid, String)> {
    let mut system_info = System::new_all();
    system_info.refresh_all();
    let mut processes = vec![];
    for (_, process) in system_info.processes() {
        processes.push((process.pid(), process.name().to_string()));
    }    
    return processes;
}

pub fn get_process_handle(pid: u32) -> Option<HANDLE> {
    unsafe {
        match CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid) {
            Ok(handle) => {
                return Some(handle);
            }
            _ => {
                None
            }
        }
    }
}