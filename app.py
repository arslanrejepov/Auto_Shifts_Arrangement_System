from fastapi import FastAPI, Request, Form
from fastapi.responses import HTMLResponse
from fastapi.templating import Jinja2Templates
import subprocess
import json
import os

app = FastAPI()

templates = Jinja2Templates(directory="templates")

# Path to C++ executable
EXECUTABLE_PATH = os.path.join("core", "prog.exe")


@app.get("/", response_class=HTMLResponse)
async def index(request: Request):
    return templates.TemplateResponse(
        "index.html",
        {
            "request": request,
            "data": None
        }
    )


@app.post("/", response_class=HTMLResponse)
async def generate_schedule(
    request: Request,
    staff_count: str = Form(...),
    day_count: str = Form(...),
    min_off: str = Form(...),
    rate: str = Form(...)
):
    data = None

    try:
        result = subprocess.run(
            [
                EXECUTABLE_PATH,
                staff_count,
                day_count,
                min_off,
                rate
            ],
            capture_output=True,
            text=True,
            check=True
        )

        output = result.stdout

        start_marker = "---JSON_START---"
        end_marker = "---JSON_END---"

        if start_marker in output and end_marker in output:
            json_str = (
                output
                .split(start_marker)[1]
                .split(end_marker)[0]
            )

            data = json.loads(json_str)

        else:
            print("JSON data not found")
            print(output)

    except Exception as e:
        print(f"C++ Error: {e}")


    return templates.TemplateResponse(
        "index.html",
        {
            "request": request,
            "data": data
        }
    )
