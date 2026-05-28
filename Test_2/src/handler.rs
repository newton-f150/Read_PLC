use axum::{
    Router,Json,routing::get,
};

use uuid::Uuid;
use serde::Serialize;
use std::net::SocketAddr;

use crate::model::{Login,Login_Response,PlcData};


pub async fn read_plc(Json(data):Json<PlcData>)-> Json<PlcData>{
    let data = PlcData{        temperature:80,
    };
    Json(data)
};
