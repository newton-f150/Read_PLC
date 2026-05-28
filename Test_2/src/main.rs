use axum::{
    Json, Router, routing::{Route, get}
};

use uuid::Uuid;
use serde::Serialize;
use std::net::SocketAddr;
use std::error::Error;

pub mod model;
pub mod handler;
use crate::model::{Login,Login_Response,PlcData};
use crate::handler::{read_plc};


#[tokio::main]
async fn main() -> Result<(),Box<dyn std::error::Error>>{
    let app = Router::new().route("/", get(read_plc));

    Ok(())
}