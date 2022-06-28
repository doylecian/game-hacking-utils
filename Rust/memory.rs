use windows::Win32::Foundation::HANDLE;
mod process;
use proces::read_mem_addr

pub enum AddressType {
    Pointer,
    Value,
}

pub fn resolve_pointer_chain(handle: HANDLE, base_addr: usize, offsets: &[usize], addr_type: AddressType) -> Option<usize> {
    let mut final_addr = base_addr;
    match addr_type {
        AddressType::Pointer => {
            for o in offsets {
                if let Some(resolved) = read_mem_addr(handle, final_addr + o, 4) {
                    final_addr = resolved;
                }
                else { return None }
            }
            return Some(final_addr)
        },
        AddressType::Value => {
            for o in &offsets[..offsets.len() - 1] {
                if let Some(resolved) = read_mem_addr(handle, final_addr + o, 4) {
                    final_addr = resolved;
                }
                else { return None }
            }
            Some(final_addr + &offsets[offsets.len() - 1])

        },
    }
}