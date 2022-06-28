use std::mem::size_of;

use sysinfo::{System, SystemExt, ProcessExt, Pid, PidExt};
use windows::Win32::{System::{Diagnostics::ToolHelp::{CreateToolhelp32Snapshot, TH32CS_SNAPMODULE32, TH32CS_SNAPMODULE, MODULEENTRY32, Module32First, PROCESSENTRY32}}, Threading::{OpenProcess, PROCESS_VM_READ, PROCESS_QUERY_INFORMATION}}, Foundation::{HANDLE, CloseHandle}}};

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

pub fn get_process_handle(pid: u32) -> Option<HANDLE> {
    let mut entry = PROCESSENTRY32::default();
    entry.dwSize = size_of::<PROCESSENTRY32>() as u32;
    unsafe {
        match CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid) {
            Ok(_handle) => {
                match OpenProcess(PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, false, pid) {
                    Ok(handle) => return Some(handle),
                    Err(_) => return None
                }
            }
            _ => None
        }
    }
}

pub fn get_process_pid(name: &str) -> Option<u32> {
    for (p_id, p_name) in get_process_list() {
        if p_name == name {
            return Some(p_id.as_u32())
        }
    }
    None
}

pub fn get_process_base_address(pid: u32) -> Option<usize> {
    let mut mod_entry = MODULEENTRY32::default();
    mod_entry.dwSize = size_of::<MODULEENTRY32>() as u32;
    unsafe {
        match CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid) {
            Ok(snapshot) => {
                if Module32First(snapshot, &mut mod_entry).as_bool() {
                    CloseHandle(snapshot);
                    return Some(mod_entry.modBaseAddr as usize);
                }
                else { return None }
            }
            _ => None
        }
    }
}

pub fn read_mem_addr(handle: HANDLE, addr: usize, buffer_size: i8) -> Option<usize> {
    let mut data: *mut c_void = ptr::null_mut();
    let lp_buffer: *mut c_void = <*mut _>::cast(&mut data);
    //let nsize = size_of::<usize>();
    let mut bytes: *mut usize = ptr::null_mut();
    let lp_bytes_read: *mut usize = <*mut _>::cast(&mut bytes);
    unsafe {
        if ReadProcessMemory(handle, addr as *const c_void, lp_buffer, buffer_size as usize, lp_bytes_read).as_bool() { return Some(data as usize) }
        else { None }
    }
}
