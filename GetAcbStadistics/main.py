from selenium import webdriver
from selenium.webdriver.common.by import By

import csv
import requests
from bs4 import BeautifulSoup

HEADER_ID = 1
#--------------------------------------------------------------------------------
# Set up the webdriver (in this case, for Chrome)
driver = webdriver.Chrome()

# Navigate to the webpage
driver.get("https://www.acb.com/resultados-clasificacion/ver")

# Find the <a> element with title="estadisticas" attribute
elements = driver.find_elements(By.CSS_SELECTOR, 'a[title="Estadísticas"]')
for elem in elements:
    # Get the href attribute of the <a> element
    href = elem.get_attribute("href")

    # ------------------------------------------------------------------------------
    response = requests.get(href)

    # Parse the HTML with BeautifulSoup
    soup = BeautifulSoup(response.text, "html.parser")

    # Get the date of the match
    section_match = soup.find('section', {'class': 'contenedora_estadisticas'})

    datos_fecha = section_match.find('div', {'class':'datos_fecha'})
    info = datos_fecha.text
    info_list = info.split(" | ")

    # ======================== LOCAL TEAM ==================================

    # Find the section with class "partido"
    section_match_local = soup.find('section', {'class': 'partido'})

    # Local Team Name
    h6_element = section_match_local.find('h6', {'class': 'colorweb_4 bg_azul_oscuro roboto_bold'})

    local_team_name_result = h6_element.text.replace(" ", "_")
    local_team_name_result = local_team_name_result.replace("\xa0\xa0", "_")
    local_team_name = local_team_name_result

    # Find the table with data-toggle="table-estadisticas"
    table = section_match_local.find("table", {"data-toggle": "table-estadisticas"})

    # Get all the rows in the table
    rows_local = table.find_all("tr")

    # ======================== GUEST TEAM ==================================

    # Find the section with class "Partido Visitante"
    section_match_guest = soup.find('section', {'class': 'partido visitante'})

    # Guest Team Name
    h6_element = section_match_guest.find('h6', {'class': 'colorweb_4 bg_azul_oscuro roboto_bold'})
    guest_team_name_result = h6_element.text.replace(" ", "_")
    guest_team_name_result = guest_team_name_result.replace("\xa0\xa0", "_")
    guest_team_name = guest_team_name_result

    # Find the table within the section
    table = section_match_guest.find("table", {"data-toggle": "table-estadisticas"})

    # Get all the rows in the table
    rows_guest = table.find_all("tr")

    # Create a CSV file and write the table data to it
    with open(local_team_name + "_VS_" + guest_team_name + "_" + info_list[0].replace(" ", "_") + "_" + info_list[1].replace("/","-") + ".csv", 'w', newline='', encoding='utf-8') as file:
        writer = csv.writer(file)


        writer.writerow(info_list)
        ## LOCAL TEAM ##
        # Row for local team name
        writer.writerow([local_team_name])

        # Leave one in blank
        writer.writerow([])

        # Write the table headers to the file
        headers = [th.text for th in rows_local[HEADER_ID].find_all("th")]
        writer.writerow(headers)

        # Write the table rows to the file
        for row in rows_local[(HEADER_ID + 1):]:
            data = [td.text for td in row.find_all("td")]

            # Finish condition
            
            if "*" in data[0]:
                data[0] = data[0].replace("*", "")

            if(data[1] == "Equipo"):
                break

            writer.writerow(data)

        ## ---------------------------------------------------------------------------- ##
        # Leave one in blank
        writer.writerow([])
        writer.writerow([])
        ## ---------------------------------------------------------------------------- ##

        ## GUEST TEAM ##
        # Row for guest team name
        writer.writerow([guest_team_name])

        # Leave one in blank
        writer.writerow([])

        # Write the table headers to the file
        headers = [th.text for th in rows_guest[HEADER_ID].find_all("th")]
        writer.writerow(headers)

        # Write the table rows to the file
        for row in rows_guest[(HEADER_ID + 1):]:
            data = [td.text for td in row.find_all("td")]

            if "*" in data[0]:
                data[0] = data[0].replace("*", "")

            # Finish condition
            if(data[1] == "Equipo"):
                break

            writer.writerow(data)

# Close the webdriver
driver.quit()