# -*- coding: utf-8 -*-
from selenium import webdriver
from selenium.webdriver.common.action_chains import ActionChains
from selenium.webdriver.common.desired_capabilities import DesiredCapabilities
from selenium.webdriver.common.by import By
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.support.ui import Select
from selenium.common.exceptions import NoSuchElementException
from selenium.common.exceptions import NoAlertPresentException
import unittest, time, re

class InstallLocal(unittest.TestCase):
    def setUp(self):
        self.driver = webdriver.Remote(command_executor='http://pcsmrcka.fit.vutbr.cz:4444/wd/hub',
            desired_capabilities=DesiredCapabilities.FIREFOX)
        self.driver.implicitly_wait(30)
        self.driver.set_window_size(1280,800)
        self.base_url = "http://pcsmrcka.fit.vutbr.cz:8123/"
        self.verificationErrors = []
        self.accept_next_alert = True
    
#Test sa prihlasi na server, vyhlada, nainstaluje a aktivuje plugin Duplicate Post
    def test_1_install(self):
        self.login()
        driver = self.driver   
        driver.find_element_by_xpath("//li[@id='menu-plugins']/a/div[2]").click()
        driver.find_element_by_css_selector("a.add-new-h2").click()
        driver.find_element_by_name("s").clear()
        driver.find_element_by_name("s").send_keys("Duplicate Post")
        driver.find_element_by_id("search-submit").click()
        driver.find_element_by_link_text("Duplicate Post").click()
        driver.find_element_by_link_text("Install Now").click()
        self.assertEqual("Installing Plugin: Duplicate Post 2.6", driver.find_element_by_css_selector("h2").text)
        driver.find_element_by_link_text("Activate Plugin").click()
        self.assertEqual("Duplicate Post", driver.find_element_by_css_selector("#duplicate-post > td.plugin-title > strong").text)

#Test sa prihlasi na server a zduplikuje post
    def test_2_clone(self):
        #prihlasenie ako admin
        self.login()
        driver = self.driver
        #zmaz vsetky prispevky
        driver.find_element_by_xpath("//li[@id='menu-posts']/a/div[3]").click()
        driver.find_element_by_id("cb-select-all-2").click()
        Select(driver.find_element_by_id("bulk-action-selector-bottom")).select_by_visible_text("Move to Trash")
        driver.find_element_by_id("doaction2").click()
        driver.find_element_by_xpath("//li[@id='menu-posts']/a/div[3]").click()
        #vytvori prispevok na testovanie
        driver.find_element_by_xpath("//li[@id='menu-posts']/a/div[3]").click()
        driver.find_element_by_css_selector("a.add-new-h2").click()
        driver.find_element_by_id("title-prompt-text").click()
        driver.find_element_by_id("title").clear()
        driver.find_element_by_id("title").send_keys("Hello world!")
        driver.find_element_by_id("post-format-status").click()
        driver.find_element_by_id("category-add-toggle").click()
        driver.find_element_by_id("newcategory").clear()
        driver.find_element_by_id("newcategory").send_keys("testCategory")
        driver.find_element_by_id("category-add-submit").click()
        driver.find_element_by_id("new-tag-post_tag").clear()
        driver.find_element_by_id("new-tag-post_tag").send_keys("testPost")
        driver.find_element_by_css_selector("input.button.tagadd").click()
        driver.find_element_by_id("publish").click()
        driver.find_element_by_xpath("//li[@id='menu-posts']/a/div[3]").click()
        #celkovy pocet prispevkov je 1
        self.assertTrue(self.is_element_present(By.LINK_TEXT, "All (1)"))
        #najdi vsetky prvky ktorych titul je Hello world!, defaultne je jeden prispevok      
        count = driver.find_elements_by_link_text("Hello world!")
        #jeden
        #self.assertEqual(len(count),1)
        #Tag je testPost
        self.assertTrue(self.is_element_present(By.LINK_TEXT, "testPost"))
        #Kategoria je testCategory
        self.assertTrue(self.is_element_present(By.LINK_TEXT, "testCategory"))
        #Format prispevku je status
        self.assertTrue(self.is_element_present(By.LINK_TEXT, "Status:"))
        #Prispevok je published
        self.assertTrue(self.is_element_present(By.LINK_TEXT, "Published (1)"))
        #############
        #sprav klon
        #############
        self.clone()
        #############
        #kontrola klonu
        #############
        #celkovy pocet prispevkov je 2
        count = driver.find_elements_by_link_text("Hello world!")
        self.assertTrue(self.is_element_present(By.LINK_TEXT, "All (2)"))
        #najdi vsetky prvky ktorych titul je Hello world!, povodny+klon  
        count = driver.find_elements_by_link_text("Hello world!")
        #dva
        self.assertEqual(len(count),2)
        #kontrola vytvorenia draftu,prave 1
        self.assertTrue(self.is_element_present(By.LINK_TEXT, "Draft (1)"))
        driver.find_element_by_link_text("Draft (1)").click()
        #Tag je testPost
        self.assertTrue(self.is_element_present(By.LINK_TEXT, "testPost"))
        #Kategoria je testCategory
        self.assertTrue(self.is_element_present(By.LINK_TEXT, "testCategory"))
        #Format prispevku je status
        self.assertTrue(self.is_element_present(By.LINK_TEXT, "Status:"))
        #vymaz klon
        self.trash()
        self.removeElementFromTrash()

#Test sa prihlasi na server, zmeni nastavenia date a zduplikuje post
    def test_3_clone_no_date(self):
        #prihlasenie ako admin
        self.login()
        driver = self.driver
        #otvorenie okna s nastaveniami
        self.settings()
        #zrusenie kopirovania datumu originalneho prispevku
        driver.find_element_by_name("duplicate_post_copydate").click()
        driver.find_element_by_css_selector("input.button-primary").click()
        driver.find_element_by_xpath("//li[@id='menu-posts']/a/div[3]").click()
        #celkovy pocet prispevkov je 1
        self.assertTrue(self.is_element_present(By.LINK_TEXT, "All (1)"))
        #############
        #sprav klon
        #############
        self.clone()
        #############
        #kontrola klonu
        #############
        #vymaz klon
        driver.find_element_by_link_text("Draft (1)").click()
        self.trash()
        self.removeElementFromTrash()
        #povolenie kopirovania datumu originalneho prispevku
        self.settings()
        driver.find_element_by_name("duplicate_post_copydate").click()
        driver.find_element_by_css_selector("input.button-primary").click()  

#Test sa prihlasi na server, zmeni nastavenia status a zduplikuje post
    def test_4_clone_status(self):
        #prihlasenie ako admin
        self.login()
        driver = self.driver
        #otvorenie okna s nastaveniami
        self.settings()
        #povolenie kopirovania statusu originalneho prispevku
        driver.find_element_by_name("duplicate_post_copystatus").click()
        driver.find_element_by_css_selector("input.button-primary").click()
        driver.find_element_by_xpath("//li[@id='menu-posts']/a/div[3]").click()
        #celkovy pocet prispevkov je 1
        self.assertTrue(self.is_element_present(By.LINK_TEXT, "All (1)"))
        #############
        #sprav klon
        #############
        self.clone()
        #############
        #kontrola klonu
        #############
        #celkovy pocet publikovanych prispevkov je 2
        self.assertTrue(self.is_element_present(By.LINK_TEXT, "Published (2)"))
        #vymaz klon
        self.trash()
        self.removeElementFromTrash()
        #zrusenie kopirovania statusu originalneho prispevku
        self.settings()
        driver.find_element_by_name("duplicate_post_copystatus").click()
        driver.find_element_by_css_selector("input.button-primary").click()

#Test sa prihlasi na server, zmeni nastavenie categories a zduplikuje post
    def test_5_clone_no_category(self):
        #prihlasenie ako admin
        self.login()
        driver = self.driver
        #otvorenie okna s nastaveniami
        self.settings()
        # zrusenie category
        driver.find_element_by_name("duplicate_post_taxonomies_blacklist[]").click()
        driver.find_element_by_css_selector("input.button-primary").click()
        driver.find_element_by_xpath("//li[@id='menu-posts']/a/div[3]").click()
        #celkovy pocet prispevkov je 1
        self.assertTrue(self.is_element_present(By.LINK_TEXT, "All (1)"))
        #############
        #sprav klon
        #############
        self.clone()
        #############
        #kontrola klonu
        #############
        #pribudol Draft
        driver.find_element_by_link_text("Draft (1)").click()
        #kontrola nenajdenia povodnej kategorie testCategory
        self.assertFalse(self.is_element_present(By.LINK_TEXT, "testCategory"))
        #vymaz klon
        self.trash()
        self.removeElementFromTrash()
        #povolenie kopirovania ketegorie
        self.settings()
        driver.find_element_by_name("duplicate_post_taxonomies_blacklist[]").click()
        driver.find_element_by_css_selector("input.button-primary").click()

#Test sa prihlasi na server, zmeni nastavenie tag a zduplikuje post
    def test_6_clone_no_tag(self):
        #prihlasenie ako admin
        self.login()
        driver = self.driver
        #otvorenie okna s nastaveniami
        self.settings()
        #zrusenie category
        driver.find_element_by_xpath("(//input[@name='duplicate_post_taxonomies_blacklist[]'])[2]").click()
        driver.find_element_by_css_selector("input.button-primary").click()
        driver.find_element_by_xpath("//li[@id='menu-posts']/a/div[3]").click()
        #celkovy pocet prispevkov je 1
        self.assertTrue(self.is_element_present(By.LINK_TEXT, "All (1)"))
        #############
        #sprav klon
        #############
        self.clone()
        #############
        #kontrola klonu
        #############
        #pribudol Draft
        driver.find_element_by_link_text("Draft (1)").click()
        #kontrola nenajdenia povodneho tagu testPost
        self.assertFalse(self.is_element_present(By.LINK_TEXT, "testPost"))
        #vymaz klon
        self.trash()
        self.removeElementFromTrash()
        #povolenie kopirovania ketegorie
        self.settings()
        driver.find_element_by_xpath("(//input[@name='duplicate_post_taxonomies_blacklist[]'])[2]").click()
        driver.find_element_by_css_selector("input.button-primary").click()

#Test sa prihlasi na server, zmeni nastavenie format a zduplikuje post
    def test_7_clone_no_format(self):
        #prihlasenie ako admin
        self.login()
        driver = self.driver
        #otvorenie okna s nastaveniami
        self.settings()
        # zrusenie format
        driver.find_element_by_xpath("(//input[@name='duplicate_post_taxonomies_blacklist[]'])[3]").click()
        driver.find_element_by_css_selector("input.button-primary").click()
        driver.find_element_by_xpath("//li[@id='menu-posts']/a/div[3]").click()
        #celkovy pocet prispevkov je 1
        self.assertTrue(self.is_element_present(By.LINK_TEXT, "All (1)"))
        #############
        #sprav klon
        #############
        self.clone()
        #############
        #kontrola klonu
        #############
        #pribudol Draft
        driver.find_element_by_link_text("Draft (1)").click()
        #Format nemoze byt status
        self.assertFalse(self.is_element_present(By.LINK_TEXT, "Status:"))
        #vymaz klon
        self.trash()
        self.removeElementFromTrash()
        #povolenie kopirovania formatu originalneho prispevku
        self.settings()
        driver.find_element_by_xpath("(//input[@name='duplicate_post_taxonomies_blacklist[]'])[3]").click()
        driver.find_element_by_css_selector("input.button-primary").click()

#Test sa prihlasi na server, zmeni nastavenia prefix a suffix
    def test_8_clone_add_fix(self):
        #prihlasenie ako admin
        self.login()
        driver = self.driver
        #otvorenie okna s nastaveniami
        self.settings()
        # pridanie suffixu a prefixu
        driver.find_element_by_name("duplicate_post_title_prefix").clear()
        driver.find_element_by_name("duplicate_post_title_prefix").send_keys("PRE")
        driver.find_element_by_name("duplicate_post_title_suffix").clear()
        driver.find_element_by_name("duplicate_post_title_suffix").send_keys("SUF")
        driver.find_element_by_css_selector("input.button-primary").click()
        driver.find_element_by_xpath("//li[@id='menu-posts']/a/div[3]").click()
        #celkovy pocet prispevkov je 1
        self.assertTrue(self.is_element_present(By.LINK_TEXT, "All (1)"))
        #############
        #sprav klon
        #############
        self.clone()
        #############
        #kontrola klonu
        #pribudol Draft
        driver.find_element_by_link_text("Draft (1)").click()
        #nazov prispevku s prefixom a suffixom
        count = driver.find_elements_by_link_text("PRE Hello world! SUF")
        #vymaz klon
        element_to_hover_over = driver.find_element_by_link_text("PRE Hello world! SUF")
        hover = ActionChains(driver).move_to_element(element_to_hover_over)
        hover.perform()
        driver.find_element_by_link_text("Trash").click()
        self.removeElementFromTrash()
        #povolenie kopirovania status originalneho prispevku, zrusenie prefixu a suffixu
        self.settings()
        driver.find_element_by_name("duplicate_post_title_prefix").clear()
        driver.find_element_by_name("duplicate_post_title_suffix").clear()
        driver.find_element_by_css_selector("input.button-primary").click()

#Test sa prihlasi na server, skontroluje, ze je nainstalovany plugin Duplicate Post a nasledne ho deaktivuje a odinstaluje   
    def test_9_delete(self):
        self.login()
        driver = self.driver
        driver.find_element_by_xpath("//li[@id='menu-plugins']/a/div[2]").click()
        self.assertEqual("Duplicate Post", driver.find_element_by_css_selector("#duplicate-post > td.plugin-title > strong").text)
        driver.find_element_by_link_text("Deactivate").click()
        driver.find_element_by_css_selector("#duplicate-post > td.plugin-title > div.row-actions.visible > span.delete > a.delete").click()
        driver.find_element_by_id("submit").click()

    def create_post(self):
        driver = self.driver
        driver.find_element_by_xpath("//li[@id='menu-posts']/a/div[3]").click()
        driver.find_element_by_css_selector("a.add-new-h2").click()
        driver.find_element_by_id("title-prompt-text").click()
        driver.find_element_by_id("title").clear()
        driver.find_element_by_id("title").send_keys("Hello world!")
        driver.find_element_by_id("post-format-status").click()
        driver.find_element_by_id("category-add-toggle").click()
        driver.find_element_by_id("newcategory").clear()
        driver.find_element_by_id("newcategory").send_keys("testCategory")
        driver.find_element_by_id("category-add-submit").click()
        driver.find_element_by_id("new-tag-post_tag").clear()
        driver.find_element_by_id("new-tag-post_tag").send_keys("testPost")
        driver.find_element_by_css_selector("input.button.tagadd").click()
        driver.find_element_by_id("publish").click()
        driver.find_element_by_xpath("//li[@id='menu-posts']/a/div[3]").click()

#metoda zmaze prispevok v kosi
    def removeElementFromTrash(self):
        driver = self.driver
        driver.find_element_by_css_selector("li.trash > a").click()
        driver.find_element_by_css_selector("div.tablenav.bottom > div.alignleft.actions > #delete_all").click()

#metoda prejde na stranku nastavenie Duplicate post pluginu   
    def settings(self):
        driver = self.driver
        driver.find_element_by_xpath("//li[@id='menu-plugins']/a/div[3]").click()
        driver.find_element_by_xpath("//tr[@id='duplicate-post']/td/div/span/a").click()

#metoda vytvori klon prispevku Hello world   
    def clone(self):
        driver = self.driver
        element_to_hover_over = driver.find_element_by_link_text("Hello world!")
        hover = ActionChains(driver).move_to_element(element_to_hover_over)
        hover.perform()
        driver.find_element_by_link_text("Clone").click()

#metoda presunie prispevok Hello world do kosa   
    def trash(self):
        driver = self.driver
        element_to_hover_over = driver.find_element_by_link_text("Hello world!")
        hover = ActionChains(driver).move_to_element(element_to_hover_over)
        hover.perform()
        driver.find_element_by_link_text("Trash").click()

#metoda na prihlasenie na stranku    
    def login(self):
        driver = self.driver
        driver.get(self.base_url + "/xzelia00/")
        driver.find_element_by_link_text("Log in").click()
        driver.find_element_by_id("user_login").clear()
        driver.find_element_by_id("user_login").send_keys("xzelia00")
        driver.find_element_by_id("user_pass").clear()
        driver.find_element_by_id("user_pass").send_keys("ykic")
        driver.find_element_by_id("wp-submit").click()
    
    def is_element_present(self, how, what):
        try: self.driver.find_element(by=how, value=what)
        except NoSuchElementException, e: return False
        return True
    
    def is_alert_present(self):
        try: self.driver.switch_to_alert()
        except NoAlertPresentException, e: return False
        return True
    
    def close_alert_and_get_its_text(self):
        try:
            alert = self.driver.switch_to_alert()
            alert_text = alert.text
            if self.accept_next_alert:
                alert.accept()
            else:
                alert.dismiss()
            return alert_text
        finally: self.accept_next_alert = True
    
    def tearDown(self):
        self.driver.quit()
        self.assertEqual([], self.verificationErrors)

if __name__ == "__main__":
    unittest.main()
