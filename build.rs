use std::env;
use std::path::PathBuf;

fn main()
{
    pkg_config::Config::new()
        .atleast_version("1.0.18")
        .probe("libsodium")
        .unwrap();

    cc::Build::new()
        .file("src/node.c")
        .include("src")
        .compile("shadowlands");

    let bindings = bindgen::Builder::default()
        .header("src/node.h")
        .allowlist_type("sh_.*")
        .allowlist_function("sh_.*")
        .allowlist_var("SH_.*")
        .impl_debug(true)
        .generate()
        .expect("Failed to generate `shadowlands` bindings!");
    let outpath = PathBuf::from(env::var("OUT_DIR").unwrap());
    bindings
        .write_to_file(outpath.join("bindings.rs"))
        .expect("Failed to write out `shadowlands` bindings!");
}
