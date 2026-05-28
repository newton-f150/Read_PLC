use serde::Serialize;
use chrono::Utc;
use uuid::Uuid;

#[derive(Serialize)]
pub struct Login{
    username:String,
    password:String,
}

#[derive(Serialize)]
pub struct Login_Response{
    timestamp:Utc,
    jwt:String,
}

#[derive(Serialize)]
pub struct PlcData{
    pub temperature:u32,

}

#[derive(Serialize)]
pub struct PlcData_Response{
    id:String,
    time:String,
    temperature:u32
}