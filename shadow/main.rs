use std::path::PathBuf;

use shadow::ffi::sh_node_create_from_filepath;

fn main()
{
    let node = sh_node_create_from_filepath();
}
